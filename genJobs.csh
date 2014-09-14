#/bin/tcsh

#�Ѿ����й���run����
@ existedRun=0000
#�����Ҫ���е�run����
@ totalRun=3000
#ÿ���ļ�����run����
@ runNumInDir=6
#�ű�����λ�ú����ݴ��λ��

set FLUWORK=`pwd` 
set dataDir=$FLUWORK/data/PART1

if ( -e $dataDir ) then
    rm $dataDir/* -rf
    echo clean $dataDir
endif

mkdir -p $dataDir/jobScripts $dataDir/rootFile
cd $dataDir/jobScripts

@ dirNum = $totalRun / $runNumInDir
#@ i=$existedRun
@ i=0
@ newseed=0
@ j=0
#while( $i < $dirNum + $existedRun)
while( $i < $dirNum)
    @ j = $i / 1000
    @ newseed = 1235298764 + $i * $runNumInDir 
    echo $newseed
    @ dirNam = $i * $runNumInDir + 1 + $existedRun
    set dirNamStr = `printf "%06d\n" $dirNam` 
    echo $dirNamStr
    mkdir -p $dirNamStr
    pushd $dirNamStr 
    sed -e "s#1235298764#${newseed}#g" $FLUWORK/JUNO.inp>JUNO.inp
    set nowDir=`pwd`
    @ i = $i + 1
    set nowJobNum=`printf "%04d\n" $i`
    set wholePath=$nowDir
    sed -e "s#DATADIR#$wholePath#g"\
        -e "s#WORKPATH#$FLUWORK#g"\
        -e "s#STARTRUNNUM#$dirNam#g"\
        -e "s#-M10#-M$runNumInDir#g" $FLUWORK/jobScriptsTemp.csh>fluka_JUNO_$nowJobNum.csh
    echo 1 >NextSeedNum
    popd
    echo qsub -q dybshortq jobScripts/$dirNamStr/fluka_JUNO_$nowJobNum.csh >>../submit.csh.$j
end
cd $dataDir
