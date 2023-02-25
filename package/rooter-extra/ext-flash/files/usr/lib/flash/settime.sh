#!/bin/sh
. /lib/functions.sh

set=$1

uci set flash.flash.time=$set
uci commit flash
if [ -e /etc/crontabs/root ]; then
	sed -i '/flash.sh/d' /etc/crontabs/root
fi
tim=$(uci -q get flash.flash.time)
HOUR=${tim:0:2}
MIN=${tim:3:2}
rand=$(uci -q get flash.flash.random)
if [ "rand" = '0' ]; then
	RANDOM=$(date +%s%N | cut -b10-19)
	range=$(( $RANDOM % 45 + 0 ))
	let MIN=$MIN+$range
	if [ "$MIN" -gt 59 ]; then
		let MIN=$MIN-60
		let HOUR=$HOUR+1
	fi
fi
echo "$MIN $HOUR * * * /usr/lib/flash/flash.sh &" >> /etc/crontabs/root
/etc/init.d/cron restart