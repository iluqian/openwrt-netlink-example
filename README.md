echo "# openwrt-netlink-example" >> README.md

git init  //初始化git

git add README.md  //git 添加文件或目录

git commit README.md -m "first commit,README.md"   // 提交单个文件

git remote add origin https://github.com/iluqian/openwrt-netlink-example.git

git push -u origin master   //首次提交之前


git status     //查看状态

git show         //查看上次代码提交

git push -u origin		//提交

git pull		//更新

git diff  //查看修改

git branch  //查看本机默认使用的分支

git branch -a //查看一共多少分支

git checkout branch-1 //将本地分支切换到branch-1

git clone //clone 源码

git clone -b branch-1 https://github.com/iluqian/openwrt-netlink-example.git  //下载一个分支到当前目录
