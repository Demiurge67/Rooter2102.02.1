// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * This program generates Sercomm's PID tag.
 *
 * Copyleft (C) 2022 Maximilian Weinmann <x1@disroot.org>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
Example:
00000000  30 30 30 31 30 32 30 30  34 33 35 30 34 41 30 30  |0001020043504A00|
00000010  30 30 30 30 30 30 30 30  30 30 30 30 30 30 30 30  |0000000000000000|
00000020  30 30 30 30 30 30 30 30  30 30 30 30 30 30 30 30  |0000000000000000|
00000030  30 30 30 30 30 30 30 30  30 30 30 30 30 30 30 30  |0000000000000000|
00000040  30 30 30 30 30 30 30 30  30 30 30 30 34 31 33 30  |0000000000004130|
00000050  33 30 33 31 30 30 30 30  30 30 30 30 30 30 30 31  |3031000000000001|
00000060  30 30 30 30 32 30 31 35  30 30 30 30 30 30 30 30  |0000201500000000|
00000070
*/

struct Sercomm_PID_t {
	uint8_t HWVER[4];	// example Beeline SmartBox TURBO+
	uint8_t str0x4[4];	// example Beeline SmartBox GIGA
	uint8_t HWID[8];	// AWI->ASCII(415749) example Beeline SmartBox PRO
	uint8_t str0x10[4];	// example WiFire S1500.NBN
	uint8_t str0x14[56];
	uint8_t str0x4c[8]; // A001->ASCII(41303031) example Speedport W 724V Typ C
	uint8_t str0x54[8];
	uint8_t str0x5c[4]; // example Speedport W 724V Typ C
	uint8_t str0x60[4];
	uint8_t SWVER[4];	// example Beeline SmartBox TURBO
	uint8_t str0x68[8];
} PID;

// https://forum.openwrt.org/t/adding-support-for-sercomm-s1500-clones-beeline-smartbox-pro-wifire-s1500-nbn/110065/17?u=maxs0nix

void usage(int status) {
	FILE *stream = (status != EXIT_SUCCESS) ? stderr : stdout;

	fprintf(stream,
"\n"
"Options:\n"
"  -a <HWVER>      Hardware version\n"
"  -b <str0x4>     example PID Beeline SmartBox GIGA\n"
"  -c <HWID>       Hardware ID\n"
"  -d <str0x10>    example PID WiFire S1500.NBN\n"
"  -e <str0x4c>    A001->ASCII(41303031) example PID Speedport W 724V Typ C\n"
"  -f <str0x5c>    example PID Speedport W 724V Typ C\n"
"  -g <SWVER>      Software version\n"
"  -o <file>       write output to the file <file>\n"
"  -h              show this screen\n"
	);

	exit(status);
}

int copy_string_check_length(uint8_t *destination, const char *source, size_t desired_length) {
	size_t length = strlen(source);
	if (length != desired_length) {
		return 0;
	}
	memcpy(destination, source, length);
	return 1;
}

static char hexconvtab[] = "0123456789ABCDEF";

int hexify_string_check_length(uint8_t *destination, const char *source, size_t maximum_length) {
	size_t length = strlen(source);
	if (length * 2 > maximum_length) {
		return 0;
	}

	size_t i, j;
	for (i = j = 0; i < strlen(source); i++) {
		destination[j++] = hexconvtab[source[i] >> 4];
		destination[j++] = hexconvtab[source[i] & 15];
	}
	return 1;
}

int main(int argc, char* argv[]) {
	memset(&PID, '0', sizeof(struct Sercomm_PID_t));
	char *pidpath = "sercomm.pid";
	int c;
	while ((c = getopt(argc, argv, "a:b:c:d:e:f:g:ho:")) != -1) {
		switch (c) {
		case 'a':
			if (!copy_string_check_length(PID.HWVER, optarg, sizeof(PID.HWVER))) {
				fprintf(stderr, "invalid HWVER length\n");
				return EXIT_FAILURE;
			}
			break;
		case 'b':
			if (!copy_string_check_length(PID.str0x4, optarg, sizeof(PID.str0x4))) {
				fprintf(stderr, "invalid str0x4 length\n");
				return EXIT_FAILURE;
			}
			break;
		case 'c': {
			if (!hexify_string_check_length(PID.HWID, optarg, sizeof(PID.HWID))) {
				fprintf(stderr, "invalid HWID length\n");
				return EXIT_FAILURE;
			}
			break;			
		}
		case 'd':
			if (!copy_string_check_length(PID.str0x10, optarg, sizeof(PID.str0x10))) {
				fprintf(stderr, "invalid str0x10 length\n");
				return EXIT_FAILURE;
			}
			break;
		case 'e': {
			if (!hexify_string_check_length(PID.str0x4c, optarg, sizeof(PID.str0x4c))) {
				fprintf(stderr, "invalid str0x4c length\n");
				return EXIT_FAILURE;
			}
			break;			
		}
		case 'f':
			if (!copy_string_check_length(PID.str0x5c, optarg, sizeof(PID.str0x5c))) {
				fprintf(stderr, "invalid str0x5c length\n");
				return EXIT_FAILURE;
			}
			break;
		case 'g':
			if (!copy_string_check_length(PID.SWVER, optarg, sizeof(PID.SWVER))) {
				fprintf(stderr, "invalid SWVER length\n");
				return EXIT_FAILURE;
			}
			break;
		case 'o':
			pidpath = optarg;
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}
	//memcpy(PID.str0x14, "0000", 56);
	//memcpy(PID.str0x54, "00000000", 8);
	//memcpy(PID.str0x60, "0000", 4);
	//memcpy(PID.str0x68, "00000000", 8);

	int filepid = open(pidpath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filepid == -1) {
		fprintf(stderr, "failed to open '%s' for writing: %s\n", pidpath, strerror(errno));
		return EXIT_FAILURE;
	}
	if (write(filepid, &PID, sizeof(struct Sercomm_PID_t)) != sizeof(struct Sercomm_PID_t)) {
		fprintf(stderr, "failed to write data: %s\n", strerror(errno));
		close(filepid);
		return EXIT_FAILURE;
	}
	close(filepid);
	return EXIT_SUCCESS;
}
