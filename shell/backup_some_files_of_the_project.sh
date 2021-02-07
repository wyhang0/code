#!/bin/bash

commandArgTest(){
	if [ $# -lt 2 ]
	then
		echo please use: $0 source_dir destination_dir
		exit
	fi
}
mkdirCmd(){
	echo "mkdir -p $1"i
	
	mkdir -p $1
	
	if [ $? != 0 ]
	then
		echo mkdir $1 failed
		exit
	fi

	echo
}
cpFileCmd(){
	echo cp -n $1 $2
	
	cp -f $1 $2

	if [ ! -e $2 ]
	then
		echo cp -n $1 $2 failed
		exit
	fi

	echo
}
cpDirCmd(){
	echo cp -rn $1 $2

        cp -rn $1 $2

        if [ `find $1 | cat -n | tail -n -1 | awk '{print $1}'` != `find $2 | cat -n | tail -n -1 | awk '{print $1}'` ]
        then
                echo cp -rn $1 $2 failed
                exit
        fi

        echo
}

//源目录
SourceDir=$1
//备份目录
DestinationDir=$2

//---------------备份项目文件-----------------
//备份夹的子目录结构
ProjectConfigDir=/device/lentek/len6737t_66_sh_n/
Arm64Dir=/kernel-3.18/arch/arm64/configs/

//创建备份夹的子目录
DirArray=($ProjectConfigDir $Arm64Dir)
//备份子目录的文件
FileArray=(${ProjectConfigDir}ProjectConfig.mk ${Arm64Dir}len6737t_66_sh_n_debug_defconfig ${Arm64Dir}len6737t_66_sh_n_defconfig)
//备份子目录的目录
FilesArray=()

commandArgTest $*

for dir in ${DirArray[*]}
do
	mkdirCmd ${DestinationDir}${dir}
done

for file in ${FileArray[*]}
do
	cpFileCmd $SourceDir$file $DestinationDir$file
done

for dir in ${FilesArray[*]}
do
	cpFileCmd $SourceDir$dir $DestinationDir$dir
done
