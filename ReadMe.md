* 初始化git

> `git init`

* 克隆一个完整的项目到当前目录下

> `git clone [url]`

* 拉取项目中的所有内容

> `git fetch [url]`

- 合并分支

> `git merge [branch]`

- 拉取项目中的所有内容到当前目录下

> 等于git fetch + git merge
>
> `git pull [url] [branch]`

- 把修改后的内容推送到远程仓库中

> （单项不能大于100M）
>
> `git push [url] [branch]`

- 添加修改项

> `git add [file]`
>
>  (git add . 添加当前目录下的所有文件)

- 添加修改项的备注

> `git commit -m "备注"`

- 添加远程仓地址的快捷名

> `git remote add [name] [url]`

- 删除远程仓地址的快捷名

> `git remote rm [name]`

- 查看所有快捷名

> `git remote -v`

- 创建分支

> `git branch [branchname]`

* 查看所有分支

> `git branch -a`

- 切换分支

> `git checkout [branchname]`
>
> 如果文件不一样则会修改文件

- 查看文件

> `ls`

- 删除分支

> `git branch -d (branchname)`

- 查看用户名

> `git config user.name`

- 查看邮箱

> `git config user.email`

- 修改用户名

> `git config --global user.name [name]`

- 修改邮箱

> `git config --global user.email [email]`

- 清除缓存

> `git rm -r --cached .`

- 查看所有提交

> `gitk`

* 撤销所有修改（未git add)

> git checkout .

* 撤销所有修改（已git add但未git commit)

> git reset HEAD .

* 撤销所有修改（已git commit)

> git reset --hard [commitid]
>
> 你可以用git log命令来查看git的提交历史和commitid