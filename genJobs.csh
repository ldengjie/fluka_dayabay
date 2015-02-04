#!/brn/tcsh

#已经运行过的run个数
@ existedRun=0
#这次需要运行的run个数
@ totalRun=2000
#每个文件夹下run个数
@ runNumInDir=20
#脚本生成位置和数据存放位置

set FLUWORK=`pwd` 
set dataDir=$FLUWORK/data/PART10

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
    @ j = $i / 120
    @ newseed = 1235598764 + $i * $runNumInDir 
    echo $newseed
    @ dirNam = $i * $runNumInDir + 1 + $existedRun
    set dirNamStr = `printf "%06d\n" $dirNam` 
    echo $dirNamStr
    mkdir -p $dirNamStr
    pushd $dirNamStr 
    sed -e "s#1235598764#${newseed}#g" $FLUWORK/LA.inp>LA.inp
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
        -e "s#-M10#-M$runNumInDir#g" $FLUWORK/jobScriptsTemp.csh>fluka_LA_$nowJobNum.csh
    echo  $n >NextSeedNum
    echo n: $n
    popd
    echo qsub -q dyb64q jobScripts/$dirNamStr/fluka_LA_$nowJobNum.csh >>../submit.csh.$j
end
cd $dataDir 
