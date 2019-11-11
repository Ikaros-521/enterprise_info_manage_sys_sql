使用的mysql数据库
    
安装MySQL数据库

```bash
sudo apt-get update
sudo apt-get install mysql-server
```

确认是否安装成功

```bash
sudo netstat -tap | grep mysql
```
当mysql节点处于LISTEN状态表示启动成功

登录数据库

```bash
mysql -u root -p
```
或者直接在-p后面跟密码，如下

```bash
mysql -uroot -proot
```
再装个mysql-client, libmysqlclient-dev

```bash
sudo apt-get install mysql-client
sudo apt-get install libmysqlclient-dev
```

操作系统 Linux Ubuntu12.04

数据库使用的MySQL，root创建 EMIS数据库，相应的表Manager，Department，Employee等可查看源码

使用说明
	1、make       编译
	2、./最终版    运行

如果遇到编译错误，可能是

Makefile需要增加-lmysqlclient
