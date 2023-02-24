#!/bin/sh

ROOTER=/usr/lib/rooter

log() {
	modlog "Check Connection $CURRMODEM" "$@"
}

CURRMODEM=$1

log "Check Conn running"
timeout=5
while [ $timeout -ge 0 ]; do
	conn=$(uci -q get modem.modem$CURRMODEM.connected)
	if [ "$conn" = '1' ]; then
		log "Normal Exit"
		exit 0
	fi
	log "$timeout"
	timeout=$((timeout-1))
	sleep 20
done
log "Modem Restart"
$ROOTER/luci/restart.sh $CURRMODEM 11