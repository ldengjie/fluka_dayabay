#!/bin/tcsh
cd /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/FAR/ana
sr
(time unbuffer root -b -q -l anaSpa.C) > /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/FAR/ana/log.anaSpa
