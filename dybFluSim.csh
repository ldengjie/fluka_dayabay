#/bin/tcsh
cd DATADIR
rfluka -e $FLUWORK/DayabayMuon -N0 -M10 dayabay 

@ startRunNum = STARTRUNNUM
@ i=0

foreach rootfile (`ls *.root`)
    @ newNam= $i + $startRunNum
    set newNamStr=`printf "fluSim_%06d.root\n" $newNam`
    mv $rootfile ../$newNamStr
    @ i = $i + 1
end

