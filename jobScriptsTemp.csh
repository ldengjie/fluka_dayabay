#!/bin/tcsh
#g++ 4.9.0
setenv PATH /afs/ihep.ac.cn/users/l/lidj/user/software/gcc-4.9.0/bin:$PATH
setenv LD_LIBRARY_PATH /afs/ihep.ac.cn/users/l/lidj/user/software/gcc-4.9.0/lib:/afs/ihep.ac.cn/users/l/lidj/user/software/gcc-4.9.0/lib64:/afs/ihep.ac.cn/users/l/lidj/user/software/mpc-0.8.1/lib:/afs/ihep.ac.cn/users/l/lidj/user/software/gmp-4.3.2/lib:/afs/ihep.ac.cn/users/l/lidj/user/software/mpfr-2.4.2/lib:$LD_LIBRARY_PATH
#root-v6
source /publicfs/dyb/user/lidj/software/root-v6-00/bin/thisroot.csh

setenv FLUWORK WORKPATH
setenv LD_LIBRARY_PATH ${FLUWORK}:$LD_LIBRARY_PATH

cd DATADIR
rfluka -e $FLUWORK/FarMuon -N0 -M10 FAR 

@ startRunNum = STARTRUNNUM
@ i=0

foreach rootfile (`ls *.root`)
    @ newNam= $i + $startRunNum
    set newNamStr=`printf "fluSim_%06d.root\n" $newNam`
    mv $rootfile ../../rootFile/$newNamStr
    @ i = $i + 1
end
cd ..
#rmo DATADIR -rf
