#/bin/tcsh

#已经运行过的run个数
<<<<<<< HEAD
@ existedRun=0
#这次需要运行的run个数
@ totalRun=100
#每个文件夹下run个数
@ runNumInDir=5
=======
@ existedRun=000
#这次需要运行的run个数
@ totalRun=1000
#每个文件夹下run个数
@ runNumInDir=1
>>>>>>> master
#脚本生成位置和数据存放位置

set FLUWORK=`pwd` 
set dataDir=$FLUWORK/data/PART36

if ( -e $dataDir ) then
    rm $dataDir/* -rf
    echo clean $dataDir
endif

mkdir -p $dataDir/jobScripts $dataDir/rootFile
cd $dataDir/jobScripts

@ dirNum = $totalRun / $runNumInDir
#@ i=$existedRun
@ i = 0
@ newseed = 0
@ j = 0
#while( $i < $dirNum + $existedRun)
while( $i < $dirNum)
<<<<<<< HEAD
    @ j = $i / 500
    @ newseed = 1236498764 + $i * $runNumInDir 
=======
    @ j = $i / 499
    @ newseed = 1235498764 + $i * $runNumInDir 
>>>>>>> master
    echo $newseed
    @ dirNam = $i * $runNumInDir + 1 + $existedRun
    set dirNamStr = `printf "%06d\n" $dirNam` 
    echo $dirNamStr
    mkdir -p $dirNamStr
    pushd $dirNamStr 
<<<<<<< HEAD
    sed -e "s#1236498764#${newseed}#g" $FLUWORK/FAR.inp>FAR.inp
=======
    sed -e "s#1235498764#${newseed}#g" $FLUWORK/dayabay.inp>dayabay.inp
>>>>>>> master
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
<<<<<<< HEAD
        -e "s#-M10#-M$runNumInDir#g" $FLUWORK/jobScriptsTemp.csh>fluka_FAR_$nowJobNum.csh
    echo  $n >NextSeedNum
    echo n: $n
    popd
    echo qsub -q dyb64q jobScripts/$dirNamStr/fluka_FAR_$nowJobNum.csh >>../submit.csh.$j
=======
        -e "s#-M10#-M$runNumInDir#g" $FLUWORK/jobScriptsTemp.csh>fluka_dyb_$nowJobNum.csh
    echo  $n >NextSeedNum
    echo n: $n
    popd
    echo qsub -q dybshortq jobScripts/$dirNamStr/fluka_dyb_$nowJobNum.csh >>../submit.csh.$j
>>>>>>> master
end
cd $dataDir 
