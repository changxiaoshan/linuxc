#! /bin/sh
res=`ps aux | grep delete_ump  | wc -l`
if [ $res -lt 2 ]
then 
	/home/admin/delete_ump /export/home/tomcat/UMP-Monitor/logs
fi	
