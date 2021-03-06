#include "managerservice_impl.h"
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include "tools.h"
#include "emis.h"


using namespace std;

#define MAX_M 10

//超级管理员登陆
bool ManagerServiceImpl::login(void)
{
	string a_name = "admin";
	string a_password = "admin";
	cout << "请输入用户名：";
	string name;
	cin >> name;

	cout << "请输入密码：";
	string password;
	char pw[20];
	getch();
	get_pw(pw,true,20);
	password = pw;
	cout << endl;

	

	if(name == a_name && password == a_password)
	{
		cout << "登陆成功" << endl;
		getch();
		return true;
	}
	else
	{
		cout << "用户名或密码错误" << endl;
		return false;
	}
}

//通过控制台显示主菜单
void ManagerServiceImpl::menu(void)
{
	cout << "****企业信息管理系统****" << endl;
	cout << "    1.增加管理员" << endl;
	cout << "    2.删除管理员" << endl;
	cout << "    3.列出所有管理员" << endl;
	cout << "    0.退出子系统" << endl;
	cout << "______________________" << endl;
}

//通过控制台处理增加管理员菜单项
void ManagerServiceImpl::add(void)
{
	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);
	
	cout << "请输入管理员id：";
	int mid;
	cin >> mid;
	cout << "请输入管理员用户名：";
	string name;
	cin >> name;
	cout << "请输入管理员密码：";
	string password;
	cin >> password;

	sprintf(cmd,"INSERT INTO Manager VALUES(%d,'%s','%s',0)",mid,name.c_str(),password.c_str());
	int ins = sql.insert(cmd);
	if(0 == ins || ins == -1)
	{
		cout << "增加失败，请查看数据是否重复" << endl;
		getch();
		getch();		
		return;
	}
	//cout << ins;

/*
	int m_num = 0;	// 现管理员数
	for(int i=0; i<MAX_M; i++)
	{
		if(m1[i]->get_id() == 0)
			continue;
		else
			m_num++;
	}
	if(m_num >= MAX_M)
	{
		cout << "管理员数已达上限，增加失败" << endl;
		getch();
		return;
	}
	cout << "请输入管理员用户名：";
	string name;
	cin >> name;
	cout << "请输入管理员密码：";
	string password;
	cin >> password;
	
	for(int i=0; i<MAX_M; i++)
	{
		if(m1[i]->get_id() == 0)
		{
			m1[i]->set_id(mid1++);
			m1[i]->set_name(name);
			m1[i]->set_password(password);
			m1[i]->set_perm(0);
			break;		
		}
	}
*/

	cout << "管理员添加成功" << endl;
	getch();
	getch();
}

//通过控制台处理删除管理员菜单项
void ManagerServiceImpl::del(void)
{
	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);
	
	cout << "请输入要删除的管理员id：";
	int mid;
	cin >> mid;

	sprintf(cmd,"DELETE FROM Manager where mid=%d",mid);
	int del = sql.remove(cmd);
	if(0 == del || del == -1)
	{
		cout << "删除失败，请查看id是否正确" << endl;
		getch();
		getch();		
		return;
	}
	cout << "管理员删除成功" << endl;
/*
	int m_num = 0;	// 现管理员数
	for(int i=0; i<MAX_M; i++)
	{
		if(m1[i]->get_id() == 0)
			continue;
		else
			m_num++;
	}
	if(m_num <= 0)
	{
		cout << "无管理员，删除失败" << endl;
		getch();
		return;
	}
	cout << "请输入要删除的管理员编号：";
	int id = 0;
	cin >> id;
	for(int i=0; i<MAX_M; i++)
	{
		if(m1[i]->get_id() == id)
		{
			m1[i]->set_id(0);
			m1[i]->set_name("0");
			cout << "管理员删除成功" << endl;
			break;
		}
		if(i==MAX_M-1)
		{
			cout << "无此管理员，删除失败" << endl;
			getch();
			return;
		}
	}
*/
	getch();
	getch();
}

//通过控制台处理列出所有管理员菜单项
void ManagerServiceImpl::list(void)
{
	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);
	sprintf(cmd,"select mid,name,prem from Manager");
	int sel = sql.select(cmd);	
	cout  << "    管理员id   ";
	cout  << "管理员用户名   ";
	cout  << "    管理员锁" << endl;
	sql.showResult();
	if(sel > 0)
	{
		cout << "输出成功" << endl;
	}

/*
	for(int i=0; i<MAX_M; i++)
	{
		if(m1[i]->get_id() != 0)
		{
			cout << "管理员id：" << m1[i]->get_id();
			cout << " ,管理员用户名：" << m1[i]->get_name();
			//cout << " ,管理员密码：" << d[i]->get_password();
			cout << "，管理员锁：" << m1[i]->get_perm() << endl;
		}	
	}
*/

	getch();
}

