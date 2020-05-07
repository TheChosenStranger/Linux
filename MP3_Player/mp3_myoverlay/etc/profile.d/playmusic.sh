#!/bin/sh
export PS1='<MUSIC_HELL> : \w\$'
modprobe snd-bcm2835

alias play="echo "commands=1">/root/HELL/commands.conf"

alias pause="echo "commands=2">/root/HELL/commands.conf"

alias next="echo "commands=3">/root/HELL/commands.conf"

alias prev="echo "commands=4">/root/HELL/commands.conf"

alias shuff="echo "commands=5">/root/HELL/commands.conf"
