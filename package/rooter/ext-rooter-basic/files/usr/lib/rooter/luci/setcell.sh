#!/bin/sh
 
ROOTER=/usr/lib/rooter

log() {
	logger -t "Lock Cell" "$@"
}

dat="$1"

dat1=$(echo $dat | tr "|" ",")
dat2=$(echo $dat1 | cut -d, -f1)
if [ $dat2 = "0" ]; then
	uci set custom.bandlock.cenable='0'
else
	ear=$(echo $dat1 | cut -d, -f2)
	pc=$(echo $dat1 | cut -d, -f3)
	ear1=$(echo $dat1 | cut -d, -f4)
	pc1=$(echo $dat1 | cut -d, -f5)
	uci set custom.bandlock.cenable='1'
	uci set custom.bandlock.earfcn=$ear
	uci set custom.bandlock.pci=$pc
	uci set custom.bandlock.earfcn1=$ear1
	uci set custom.bandlock.pci1=$pc1
fi
uci commit custom

ifname1="ifname"
if [ -e /etc/newstyle ]; then
	ifname1="device"
fi


CURRMODEM=$(uci get modem.general.miscnum)
COMMPORT="/dev/ttyUSB"$(uci get modem.modem$CURRMODEM.commport)
CPORT=$(uci -q get modem.modem$CURRMODEM.commport)
ATCMDD="AT+CFUN=1,1"
OX=$($ROOTER/gcom/gcom-locked "/dev/ttyUSB$CPORT" "run-at.gcom" "$CURRMODEM" "$ATCMDD")
log "Hard modem reset done on /dev/ttyUSB$CPORT to reload drivers"
ifdown wan$CURRMODEM
uci delete network.wan$CURRMODEM
uci set network.wan$CURRMODEM=interface
uci set network.wan$CURRMODEM.proto=dhcp
uci set network.wan$CURRMODEM.${ifname1}="wan"$CURRMODEM
uci set network.wan$CURRMODEM.metric=$CURRMODEM"0"
uci commit network
/etc/init.d/network reload
ifdown wan$CURRMODEM
echo "1" > /tmp/modgone
log "Setting Modem Removal flag (1)"
