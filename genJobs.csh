#/bin/tcsh

#已经运行过的run个数
@ existedRun=35660
#这次需要运行的run个数
@ totalRun=4000
#每个文件夹下run个数
@ runNumInDir=20
#脚本生成位置和数据存放位置

set FLUWORK `pwd` 
set dataDir=$FLUWORK/data/PART8

mkdir -p $dataDir/jobScripts $dataDir/rootFile
cd $dataDir/jobScripts
if ( -e ../submit.csh ) then
    rm ../submit.csh
endif

@ dirNum = $totalRun / $runNumInDir
#@ i=$existedRun
@ i=0
@ newseed=0
#while( $i < $dirNum + $existedRun)
while( $i < $dirNum)
    @ newseed = 1235198764 + $i * $runNumInDir 
    echo $newseed
    @ dirNam = $i * $runNumInDir + 1 + $existedRun
    set dirNamStr = `printf "%06d\n" $dirNam` 
    echo $dirNamStr
    mkdir -p $dirNamStr
    pushd $dirNamStr 
    sed -e "s#1235198764#${newseed}#g" $FLUWORK/LA.inp>LA.inp
    set nowDir=`pwd`
    @ i = $i + 1
    set nowJobNum=`printf "%04d\n" $i`
    set wholePath=$nowDir
    sed -e "s#DATADIR#$wholePath#g"\
    sed -e "s#WORKPATH#$FLUWORK#g"\
        -e "s#STARTRUNNUM#$dirNam#g"\
        -e "s#-M10#-M$runNumInDir#g" $FLUWORK/jobScriptsTemp.csh>fluka_$nowJobNum.csh
    echo 1 >NextSeedNum
    popd
    echo qsub -q dyb64q jobScripts/$dirNamStr/fluka_$nowJobNum.csh >>../submit.csh
end
cd $dataDir
