#!/bin/bash

sourceDir="/srv"
destinationDir="/home/git/respositories_backup"
gitUrl="git@140.143.151.11"
respositories=$(ssh git@140.143.151.11 "cd ${sourceDir}; ls")

mkdir ${destinationDir}

for respository in $respositories
do
	cd ${destinationDir}
	echo "git clone --mirror ${gitUrl}:${sourceDir}/${respository} ${respository}"
	git clone --mirror ${gitUrl}:${sourceDir}/${respository} ${respository}
	
	cd ${respository}
	echo "git remote update"
	git remote update
done

#通过crontab添加定时任务：
#        crontab –e   # 在定时任务中添加: 0 0 * * * sh /srv/backup_remote_git.sh，然后保存
#        systemctl restart cron  # 重启cron服务，如果在centos是systemctl restart crond
