#/bin/tcsh

#已经运行过的run个数
@ existedRun=0
#这次需要运行的run个数
@ totalRun=1000
#每个文件夹下run个数
@ runNumInDir=20
#脚本生成位置和数据存放位置
set dataDir="/afs/ihep.ac.cn/users/l/lidj/largedata/flukaWork/dayabay/data/test2"

mkdir -p $dataDir/jobScripts $dataDir/rootFile
cd $dataDir/jobScripts
if ( -e submit.csh ) then
    rm submit.csh
endif

@ dirNum = $totalRun / $runNumInDir
@ i=$existedRun
@ newseed=0
while( $i < $dirNum + $existedRun)
    @ newseed = 1234598765 + $i * $runNumInDir 
    echo $newseed
    @ dirNam = $i * $runNumInDir + 1
    set dirNamStr = `printf "%06d\n" $dirNam` 
    echo $dirNamStr
    mkdir -p $dirNamStr
    pushd $dirNamStr 
    sed -e "s#1234598765#${newseed}#g" $FLUWORK/dayabay.inp>dayabay.inp
    set nowDir=`pwd`
    @ i = $i + 1
    set nowJobNum=`printf "%04d\n" $i`
    set wholePath=$nowDir
    sed -e "s#DATADIR#$wholePath#g"\
        -e "s#STARTRUNNUM#$dirNam#g"\
        -e "s#-M10#-M$runNumInDir#g" $FLUWORK/jobScriptsTemp.csh>fluka_$nowJobNum.csh
    popd
    echo qsub -q dyb64q jobScripts/$dirNamStr/fluka_$nowJobNum.csh >>../submit.csh
end
cd $dataDir
