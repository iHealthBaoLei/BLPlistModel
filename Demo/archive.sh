#  archive.sh
#
#
#  Created by Lei Bao on 2017/8/25.
#

#!/bin/bash

#计时
SECONDS=0

#假设脚本放置在与项目相同的路径下
project_path=$(pwd)
#取当前时间字符串添加到文件结尾
now=$(date +"%Y_%m_%d_%H_%M_%S")

#指定项目的scheme名称
scheme="Demo"
#指定要打包的配置名
configuration="development"
#指定打包所使用的输出方式，目前支持app-store, package, ad-hoc, enterprise, development, 和developer-id，即xcodebuild的method参数
export_method='development'

#指定项目地址
workspace_path="$project_path/Demo.xcodeproj"
#指定输出路径
output_path="/Users/baolei/Downloads"
#指定输出归档文件地址
archive_path="$output_path/Demo_${now}.xcarchive"
#指定输出ipa地址
ipa_path="$output_path/Demo_${now}.ipa"
#指定输出ipa名称
ipa_name="abc_${now}.ipa"
#获取执行命令时的commit message
commit_msg="$1"

#输出设定的变量值
echo "===workspace path: ${workspace_path}==="
echo "===archive path: ${archive_path}==="
echo "===ipa path: ${ipa_path}==="
echo "===export method: ${export_method}==="
echo "===commit msg: $1==="

#先清空前一次build
gym --project ${workspace_path} --scheme ${scheme} --clean --configuration ${configuration} --archive_path ${archive_path} --export_method ${export_method} --output_directory ${output_path} --output_name ${ipa_name}

#输出总用时
echo "===Finished. Total time: ${SECONDS}s==="


