#!/bin/tcsh
sr
cd /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/ana
(time unbuffer root -b -q -l isoYield.C) > /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/ana/log.isoYield.10
