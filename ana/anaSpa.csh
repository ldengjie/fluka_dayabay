#!/bin/bash
cd /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/FAR/ana
source ~/.root.v6.sh
(time unbuffer root -b -q -l anaSpa.C) > /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/FAR/ana/log.anaSpa
