#! /bin/bash
while read line
do
    ip=`echo $line | awk -F',' '{print $1}'`
    curl -s  http://www.cip.cc/$ip | grep "数据二" | awk -F'\\|' '{print $2}'
done < $1
