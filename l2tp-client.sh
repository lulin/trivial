#!/bin/sh

PIDFILE=/var/run/xl2tpd.pid
L2TP_PIPE=/var/run/xl2tpd/l2tp-control
CONFILE=/tmp/xl2tpd.conf

start() {
    wan_proto=$(nvram get wan_proto)
    vpnc_enable=$(nvram get vpnc_enable)
    [ -z "$vpnc_enable" ] && vpnc_enable=0

    if [ "$wan_proto" != "l2tp" -a $vpnc_enable -eq 0 ]; then
        echo "Neither is WAN protocol L2TP, nor is VPN client enabled"
        exit 1
    fi

    # config
    > "$CONFILE"

    # Add global
    config_add_global "$CONFILE"

    # setup for wan l2tp mode
    if [ "$wan_proto" == "l2tp" ]; then
        wan_lac="wan_l2tp"
        wan_lns=$(nvram get wan_l2tp_server)
        wan_optfile="/tmp/wan_l2tp.options"
        config_add_lac $CONFILE "$wan_lac" "$wan_lns" "$wan_optfile"
    fi

    # setup for vpn l2tp client
    if [ $vpnc_enable -ne 0 ]; then
        vpnc_lac="vpnc_l2tp"
        vpnc_lns=$(nvram get vpnc_name)
        vpnc_optfile="/tmp/vpnc_l2tp.options"
        config_add_lac $CONFILE "$vpnc_lac" "$vpnc_lns" "$vpnc_optfile"
    fi

    xl2tpd -c $CONFILE &

    local count=0
    while [ ! -p $L2TP_PIPE ]; do
        ((count++))
        if [ $count -gt 5 ]; then
            echo "start xl2tpd failed, pipe $L2TP_PIPE missing"
            exit 1
        fi
        sleep 1
    done

    # connect wan, if setup
    if [ "$wan_proto" == "l2tp" ]; then
        username="$(nvram get wan_l2tp_username)"
        password="$(nvram get wan_l2tp_password)"
        build_optfile "$wan_optfile" "$username" "$password"
        xl2tpd-control add $wan_lac
        xl2tpd-control connect $wan_lac
    fi

    # connect vpn, if setup
    if [ $vpnc_enable -ne 0 ]; then
        username="$(nvram get vpnc_name)"
        password="$(nvram get vpnc_password)"
        build_optfile "$vpnc_optfile" "$username" "$password"
        xl2tpd_control add $vpnc_lac
        xl2tpd_control connect $vpnc_lac
    fi
}

stop() {
    kill -TERM $(cat $PIDFILE)
}

restart() {
    stop
    # wait until stopped
    local count=0
    while [ $(proc_alive) == "true" ]; do
        if [ $count -gt 5 ]; then
            echo "failed to stop xl2tpd"
            exit 1
        fi

        sleep 1
        ((count++))
    done

    start
}

proc_alive() {
    local proc="$1"

    ps |grep "$proc"|grep -v grep >/dev/null
    ret=$?
    test $ret -eq 0 && echo true && return
    echo false && return
}

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
[lac $lac]
pppoptfile = $optfile
lns = $lns
name = default
require authentication = no
tunnel rws = 8
redial = yes
redial timeout = 15
tx bps = 100000000
rx bps = 100000000
EOF
}

$1
