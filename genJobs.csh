#!/brn/tcsh

#�Ѿ����й���run����
@ existedRun=0
#�����Ҫ���е�run����
@ totalRun=1000
#ÿ���ļ�����run����
@ runNumInDir=1
#�ű�����λ�ú����ݴ��λ��

set FLUWORK=`pwd` 
set dataDir=$FLUWORK/data/PART34

if ( -e $dataDir ) then
    rm $dataDir/* -rf
    echo clean $dataDir
endif

mkdir -p $dataDir/jobScripts $dataDir/rootFile $dataDir/bak
cd $dataDir/jobScripts

@ dirNum = $totalRun / $runNumInDir
#@ i=$existedRun
@ i=0
@ newseed=0
@ j=0
#while( $i < $dirNum + $existedRun)
while( $i < $dirNum)
    @ j = $i / 120
    @ newseed = 1231098764 + $i * $runNumInDir 
    echo $newseed
    @ dirNam = $i * $runNumInDir + 1 + $existedRun
    set dirNamStr = `printf "%06d\n" $dirNam` 
    echo $dirNamStr
    mkdir -p $dirNamStr
    pushd $dirNamStr 
#sed -e "s#1231098764#${newseed}#g" $FLUWORK/FAR.inp>FAR.inp
    sed -e "s#1231098764#1231098764#g" $FLUWORK/FAR.inp>FAR.inp
    set nowDir=`pwd`
    if (  $runNumInDir % 10 == 0 ) then
        @ n = 1 
    else
        @ n = 1 + ( $i % ( 10 / ( $runNumInDir % 10 ) ) ) * 100000 * ( $runNumInDir % 10)
    endif
    @ i = $i + 1
    set nowJobNum=`printf "%04d\n" $i`
    set wholePath=$nowDir
    sed -e "s#DATADIR#$wholePath#g"\
        -e "s#WORKPATH#$FLUWORK#g"\
        -e "s#STARTRUNNUM#$dirNam#g"\
        -e "s#-M10#-M$runNumInDir#g" $FLUWORK/jobScriptsTemp.sh>fluka_$nowJobNum.sh
    echo  $n >NextSeedNum
    echo n: $n
    if ( $i == 1 ) then
        cp fluka_$nowJobNum.sh $dataDir
    endif
    popd
    echo qsub -q dybshortq jobScripts/$dirNamStr/fluka_$nowJobNum.sh >>../submit.sh.$j
end
cd $dataDir 
echo doing backup 
mv *.sh bak
cp $FLUWORK/*.inp bak
cp $FLUWORK/*.f bak
cp $FLUWORK/*.cpp bak
cp $FLUWORK/*.h bak
cp $FLUWORK/FarMuon bak
echo done!
