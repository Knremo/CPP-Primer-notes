# 1.1
系统查看返回值：`echo $?`(Unix,Powershell),`echo %ERRORLEVEL%`(Windows)
# 1.2
`iostream`库

基础类型：`istream`,`ostream`

标准输入输出对象：`cin`,`cout`,`cerr`,`clog`

`<<`和`>>`返回其左侧运算对象
# 1.4
文件结束符：`Crtl+Z`+`Enter`(Windows),`Crtl+D`(Unix)
# 1.5
## 文件重定向
Powershell:`Get-Content .\text|.\demo.exe`

Unix:`demo <infile`

# others
## Git
`git config user.name '你的名字' -g`
`git congif user.email '你的邮箱' -g`
`git init` //新建仓库
`git add README.md` //索引
`git commit -m "first commit"` //提交
`git remote add origin git@github.com:plusczh/vscode-demo.git` //远程仓库
`git push -u origin master` //push
`git pull origin master` //pull
`ssh-kegen -t rsa -b 4096 -C "email"`
`cat ~/.ssh/id_rsa.pub` //SSH key
## Github
忽略的文件和文件夹名添加到`.gitignore`