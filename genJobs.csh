#/bin/tcsh

#�Ѿ����й���run����
@ existedRun=35660
#�����Ҫ���е�run����
@ totalRun=4000
#ÿ���ļ�����run����
@ runNumInDir=20
#�ű�����λ�ú����ݴ��λ��

set FLUWORK=`pwd` 
set dataDir=$FLUWORK/data/PART8

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
    @ newseed = 1235198764 + $i * $runNumInDir 
    echo $newseed
    @ dirNam = $i * $runNumInDir + 1 + $existedRun
    set dirNamStr = `printf "%06d\n" $dirNam` 
    echo $dirNamStr
    mkdir -p $dirNamStr
    pushd $dirNamStr 
    sed -e "s#1235198764#${newseed}#g" $FLUWORK/FAR.inp>FAR.inp
    set nowDir=`pwd`
    @ i = $i + 1
    set nowJobNum=`printf "%04d\n" $i`
    set wholePath=$nowDir
    sed -e "s#DATADIR#$wholePath#g"\
        -e "s#WORKPATH#$FLUWORK#g"\
        -e "s#STARTRUNNUM#$dirNam#g"\
        -e "s#-M10#-M$runNumInDir#g" $FLUWORK/jobScriptsTemp.csh>fluka_$nowJobNum.csh
    echo 1 >NextSeedNum
    popd
    echo qsub -q dyb64q jobScripts/$dirNamStr/fluka_dayabay_$nowJobNum.csh >>../submit.csh.$j
end
cd $dataDir
