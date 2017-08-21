#!/bin/sh

CONFILE=/tmp/pptp.conf

start() {
    pppd pty "pptp $g_account_peer --nolaunchpppd" \
         file "$optfile" \
         remotename default \
         ipparam pptp \
         name $username \
         password $password
}

stop() {
    killall -9 pptp
}

restart() {
    stop_pptp
    start_pptp
}

build_config_file_for_pptp() {
    cat <<EOF > "$1"
lock
noauth
nobsdcomp
nodeflate
refuse-pap
refuse-eap
refuse-chap
refuse-mschap
require-mppe-128
EOF
}

$1
