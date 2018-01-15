update: 大概都好了ORZ
		



push用：
（按顺序用这三个）
git add <filename> // git add *          update all files in current dir
git commit -m "Commit message"  // message可以随便改
git push origin master          // push到master分支上 
					            // 也可以 git push origin <branchname> push到其他分支上
					            // 防止push上去的东西有问题又已经把原来master的覆盖掉

pull用：
git pull

建branch(1+2)：
1.git checkout -b <name> // 建branch 同时切换到此branch
2.git push origin <branch> 

git checkout master // 切回master
git branch -d <name> // delete branch

replace local file with remote one:
git checkout -- <filename>
# CC3K
