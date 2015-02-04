#!/bin/tcsh
cd /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/ana
sr
(time unbuffer root -b -q -l anaSpa.C) > /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/LA/ana/log.anaSpa
