#!/bin/sh

PIDFILE=/var/run/xl2tpd.pid
L2TP_PIPE=/var/run/xl2tpd/l2tp-control

start() {
}

stop() {
    kill -TERM $(cat $PIDFILE)
}

restart() {
    stop
    # wait until stopped
    while [ "$(ps|grep l2tp|grep -v grep)" ]; do
        sleep 1
    done
    start
}

reload() {
    check_wan_l2tp
    config
    restart
}

check_wan_l2tp() {}

build_optfile() {
    local optfile username password
    optfile="$1"
    username="$2"
    password="$3"
    cat <<EOF >"$optfile"
noauth
user $username
password "$password"
refuse-eap
mtu 1450
mru 1450
maxfail 0
holdoff 10
ipcp-accept-remote ipcp-accept-local
noipdefault
usepeerdns
default-asyncmap
nopcomp noaccomp
novj nobsdcomp nodeflate
lcp-max-terminate 0
lcp-echo-interval 20
lcp-echo-failure 6
unit 5
ktune
EOF
}

config_add_global() {
    cat <<EOF >> "$1"
[global]
port = 1701
access control = no
rand source = dev
EOF
}

config_add_lac() {
    local confile lac optfile
    confile="$1"
    lac="$2"
    lns="$3"
    optfile="$4"
    cat <<EOF >> "$confile"
[lac $g_lac]
pppoptfile = $optfile
lns = $lns
name = default
require authentication = no
tunnel rws = 8
autodial = yes
redial = yes
redial timeout = 15
tx bps = 100000000
rx bps = 100000000
EOF
}
