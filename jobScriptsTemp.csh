#/bin/tcsh

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
