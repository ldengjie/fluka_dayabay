#!/bin/sh
cd /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/ana
source ~/.root.v6.sh
(time unbuffer root -b -q -l anaSpa.C) > /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/ana/log.anaSpa
