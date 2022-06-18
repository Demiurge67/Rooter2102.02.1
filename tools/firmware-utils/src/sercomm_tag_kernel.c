// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * This program generates a Sercomm kernel header tag 
 * (probably only used for mt7621).
 *
 * Thanks for helping me with this research:
 * Karim Dehouche <karimdplay@gmail.com>
 * Mikhail Zhilkin <csharper2005@gmail.com>
 *
 * Copyright (C) 2022 Maximilian Weinmann <x1@disroot.org>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include <byteswap.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "cyg_crc.h"

#if __BYTE_ORDER == __BIG_ENDIAN
#define cpu_to_le32(x)	bswap_32(x)
#elif __BYTE_ORDER == __LITTLE_ENDIAN
#define cpu_to_le32(x)	(x)
#else
#error "Unsupported endianness"
#endif

/*
Example:
00000000: 5365 7200  Ser.
00000004: 2e6f 9601  .o..
00000008: 0020 31e2  . 1.
0000000c: 02ff ffff  ....
00000010: 0001 7001  ..p.
00000014: 2e6e 2600  .n&.
00000018: 639d 177c  c..|
0000001c: 0000 0000  ....
00000020: ffff ffff  ....
00000024: ffff ffff  ....
00000028: 0000 f001  ....
0000002c: 0000 3e01  ..>.
00000030: 7ca3 482c  |.H,
00000034: 0000 0000  ....
00000038: ffff ffff  ....
*/

struct Sercomm_Tag_Header_Kernel_t {
	uint8_t signSer[4];		// Signature Sercomm
	uint32_t str0x4;		// Start address Kernel + Size Kernel
	uint32_t crcTag;		// CRC32 Tag Header Kernel
	uint8_t str0xC[4];		// Constant (Number of slots?)
	uint32_t addrKern;		// Start address Kernel 
	uint32_t sizeKern;		// Size Kernel
	uint32_t crcKern;		// CRC32 Kernel
	uint32_t str0x1c;		// 0x00000000
	uint32_t str0x20;		// 0xFFFFFFFF
	uint32_t str0x24;		// 0xFFFFFFFF
	uint32_t addrRootfs;	// Start address RootFS 
	uint32_t sizeRootfs;	// Size RootFS
	uint32_t crcRootfs;		// CRC32 RootFS
	uint32_t str0x34;		// 0x00000000
	uint8_t str0x38[200];	// 0xFFFFFFFF
} HDR;

void usage(int status) {
	FILE *stream = (status != EXIT_SUCCESS) ? stderr : stdout;

	fprintf(stream,
"\n"
"Options:\n"
"  -a <addres>     Start address Kernel (ex. 0x1700100 - Slot1)\n"
"  -b <addres>     Start address RootFS (ex. 0x1f00000 - Slot1)\n"
"  -c <file>       read kernel image from the file <file>\n"
"  -d <file>       read rootfs image from the file <file>\n"
"  -e <file>       write output to the file <file>\n"
"  -f              Hack rootfs - read first 4 byte rootfs\n"
"  -h              show this screen\n"
	);

	exit(status);
}

int string_to_uint32(const char *source, uint32_t *destination) {
	char *end = NULL;
	uint32_t result = strtoul(source, &end, 0);
	if ((end == source) || *end) {
		return 0;
	}
	*destination = cpu_to_le32(result);
	return 1;
}

uint32_t min(uint32_t a, uint32_t b) {
	return a < b ? a : b;
}

int calculate_crc32_file(const char *path, size_t limit, uint32_t *crc32, uint32_t *size) {
	int pfd = open(path, O_RDONLY);
	if (pfd == -1) {
		return errno;
	}

	if (limit == 0) {
		struct stat st;
		if (fstat(pfd, &st) == -1) {
			close(pfd);
			return errno;
		}
		limit = st.st_size;
	}

	char buf[4096];
	size_t remaining = limit;
	uint32_t value = 0;
	while (remaining) {
		int bytes = read(pfd, buf, min(remaining, sizeof(buf)));
		if (bytes == -1) {
			int err = errno;
			close(pfd);
			return err;
		}
		if (!bytes) {
			break;
		}
		value = cyg_ether_crc32_accumulate(value, buf, bytes);
		remaining -= bytes;
	}
	if (remaining) {
		close(pfd);
		return EOVERFLOW;
	}
	*crc32 = cpu_to_le32(value);
	*size = cpu_to_le32(limit);

	close(pfd);
	return 0;
}

int main(int argc, char* argv[]) {
	memset(&HDR, 0xFF, sizeof(HDR));
	HDR.str0xC[0] = 2;	// 0x02FFFFFF
	HDR.str0x1c = 0;
	HDR.str0x34 = 0;
	size_t rootfs_limit = 0;
	char *kernaddr, *rootaddr, *kernpath, *rootpath;
	kernaddr = rootaddr = kernpath = rootpath = NULL;
	char *tagpath = "sercomm_kernel.tag";
	int c;
	while ((c = getopt(argc, argv, "a:b:c:d:e:fh")) != -1) {
		switch (c) {
		case 'a':
			kernaddr = optarg;
			break;
		case 'b':
			rootaddr = optarg;
			break;
		case 'c':
			kernpath = optarg;
			break;
		case 'd':
			rootpath = optarg;
			break;
		case 'e':
			tagpath = optarg;
			break;
		case 'f':
			rootfs_limit = 4;	// Hack read first 4 byte rootfs	
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}
	if (kernaddr == NULL || !string_to_uint32(kernaddr, &HDR.addrKern)) {
		fprintf(stderr, "invalid or missing kernel start address\n");
		return EXIT_FAILURE;
	}
	if (rootaddr == NULL || !string_to_uint32(rootaddr, &HDR.addrRootfs)) {
		fprintf(stderr, "invalid or missing rootfs start address\n");
		return EXIT_FAILURE;
	}
	int err;
	if ((err = calculate_crc32_file(kernpath, 0, &HDR.crcKern, &HDR.sizeKern))) {
		fprintf(stderr, "failed to calculate kernel crc32: %s\n", strerror(err));
		return EXIT_FAILURE;
	}
	if ((err = calculate_crc32_file(rootpath, rootfs_limit, &HDR.crcRootfs, &HDR.sizeRootfs))) {
		fprintf(stderr, "failed to calculate root fs crc32: %s\n", strerror(err));
		return EXIT_FAILURE;
	}
	HDR.str0x4 = cpu_to_le32(HDR.addrKern + HDR.sizeKern);
/*	At the time of calculation CRC32 Tag Header Kernel, 
	Signature Sercomm (0x0) & CRC32 Tag Header Kernel (0x8) 
	are filled with 0xFFFFFFFF.*/
	HDR.crcTag = cpu_to_le32(cyg_ether_crc32(&HDR, sizeof(HDR)));
	memcpy(HDR.signSer, "Ser\x00", 4);

	int filetag = open(tagpath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filetag == -1) {
		fprintf(stderr, "failed to open '%s' for writing: %s\n", tagpath, strerror(errno));
		return EXIT_FAILURE;
	}
	if (write(filetag, &HDR, sizeof(HDR)) != sizeof(HDR)) {
		fprintf(stderr, "failed to write data: %s\n", strerror(errno));
		close(filetag);
		return EXIT_FAILURE;
	}
	close(filetag);
	return EXIT_SUCCESS;
}

// gcc sercomm_tag_kernel.c -o sercomm_tag_kernel.out && ./sercomm_tag_kernel.out -a 0x1700100 -b 0x1f00000 -c 2015.4.kern.bin -d 2015.5.rootfs.bin -e kerntag.bin && xxd -c 4 -l 56 kerntag.bin
