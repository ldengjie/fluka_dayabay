#!/bin/sh
source ~/.root.v6.sh 
cd /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/ana
(time unbuffer root -b -q -l isoYield.C) > /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/ana/log.isoYield.all
