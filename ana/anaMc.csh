#!/bin/tcsh
cd /afs/ihep.ac.cn/users/l/lidj/file/NeutronYield/job
sr
(time unbuffer root -b -q -l anaMc.C) > /afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/ana/log.anaMc.2
