#!/bin/sh
alias rmo='/bin/rm'
#g++ 4.9.0
export PATH=/afs/ihep.ac.cn/users/l/lidj/user/software/gcc-4.9.0/bin:$PATH
export LD_LIBRARY_PATH=/afs/ihep.ac.cn/users/l/lidj/user/software/gcc-4.9.0/lib:/afs/ihep.ac.cn/users/l/lidj/user/software/gcc-4.9.0/lib64:/afs/ihep.ac.cn/users/l/lidj/user/software/mpc-0.8.1/lib:/afs/ihep.ac.cn/users/l/lidj/user/software/gmp-4.3.2/lib:/afs/ihep.ac.cn/users/l/lidj/user/software/mpfr-2.4.2/lib:$LD_LIBRARY_PATH
#fluka
export FLUPRO=/afs/ihep.ac.cn/users/l/lidj/user/software/fluka
export PATH=${FLUPRO}:${FLUPRO}/flutil:$PATH
export FLUFOR=gfortran
#root-v6
pushd /publicfs/dyb/user/lidj/software/root-v6-00/
source bin/thisroot.sh
popd

export FLUWORK=WORKPATH
export LD_LIBRARY_PATH=${FLUWORK}:$LD_LIBRARY_PATH

cd DATADIR
rfluka -e $FLUWORK/LaMuon -N0 -M10 LA 

startRunNum=STARTRUNNUM

i=0

for rootfile in `ls *.root`
do
    newNam=`expr $i + $startRunNum`
    newNamStr=`printf "fluSim_%06d.root\n" $newNam`
    mv $rootfile ../../rootFile/$newNamStr
    i=`expr $i + 1`
done
cd ..
#rmo DATADIR -rf
