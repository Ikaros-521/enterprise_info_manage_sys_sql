#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "department.h"
#include <fstream>
#include "service_impl.h"
#include "manager.h"
#include "tools.h"
#include "emis.h"

using namespace std;

#define MAX_M 10
#define MAX_D 10
#define MAX_E 30

void ServiceImpl::menu(void)//显示运营管理子菜单
{
	cout << "****企业信息管理系统****" << endl;
	cout << "    1.增加部门" << endl;
	cout << "    2.删除部门" << endl;
	cout << "    3.列出部门" << endl;
	cout << "    4.增加员工" << endl;
	cout << "    5.删除员工" << endl;
	cout << "    6.修改员工信息" << endl;
	cout << "    7.列出部门员工" << endl;
	cout << "    8.列出所有员工" << endl;
	cout << "    0.退出子系统" << endl;
	cout << "______________________" << endl;
}

bool ServiceImpl::manager_login(void)
{
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

	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);
	sprintf(cmd,"select name from Manager where name=\"%s\"",name.c_str());
	int sel = sql.select(cmd);
	if(sel > 0)
	{
		//cout << "成功查询到帐号" << endl;
		//cout << "sel:" << sel << endl;
		sprintf(cmd,"select password from Manager where name=\"%s\" and password=\"%s\"",name.c_str(),pw);
		int sel2 = sql.select(cmd);
		if(sel2 > 0)
		{
			//cout << "sel2:" << sel2 << endl;
			return true;
		}
		//cout << "sel2:" << sel2 << endl;	
	}
	//cout << "sel:" << sel << endl;

// 文本读写
/*
	for(int i=0; i<MAX_M; i++)
	{
		if(name == m[i]->get_name())
		{
			if(m[i]->get_perm() >= 3)
			{
				cout << "您的帐号已被锁定，请联系超级管理员解锁" << endl;
				return false;
			}
			if(password == m[i]->get_password())
			{
				cout << "登陆成功" << endl;
				getch();
				return true;
			}
			else
			{
				cout << "用户名或密码错误" << endl;
				long perm = m[i]->get_perm();
				m[i]->set_perm(++perm);
				return false;
			}
		}
		if(i == MAX_M-1)
		{
			cout << "用户名或密码错误" << endl;
			return false;
		}
	}
*/

	return false;
}


void ServiceImpl::addDept(void)//增加部门菜单项
{
	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);
	cout << "请输入部门名：";
	string name;
	cin >> name;
	sprintf(cmd,"insert into Department VALUES(%d,'%s',0)",did++,name.c_str());
	int ins = sql.insert(cmd);
	if(0 == ins || ins == -1)
	{
		cout << "增加失败，请查看数据是否重复" << endl;
		getch();
		getch();		
		return;
	}

/*
	int d_num = 0;	// 现部门数
	for(int i=0; i<MAX_D; i++)
	{
		if(d[i]->get_id() == 0)
			continue;
		else
			d_num++;
	}
	if(d_num >= MAX_D)
	{
		cout << "部门已达上限，增加失败" << endl;
		getch();
		return;
	}
	cout << "请输入部门名：";
	string name;
	cin >> name;
	
	for(int i=0; i<MAX_D; i++)
	{
		if(d[i]->get_id() == 0)
		{
			d[i] = new Department(did++,name,0);
			break;		
		}
	}

*/
	cout << "部门添加成功" << endl;
	getch();
	getch();
}
void ServiceImpl::deleteDept(void)//删除部门菜单项
{
	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);

	cout << "请输入要删除的部门id：";
	int did;
	cin >> did;

	sprintf(cmd,"DELETE FROM Department where did=%d",did);
	int del = sql.remove(cmd);
	if(0 >= del)
	{
		cout << "删除失败，请查看id是否正确" << endl;
		getch();
		getch();		
		return;
	}

	sprintf(cmd,"DELETE FROM Employee where did=%d",did);
	int del2 = sql.remove(cmd);
	if(del2 > 0)
	{
		cout << "该部门员工删除成功" << endl;
	}
	else
		cout << "该部门无员工" << endl;

/*
	int d_num = 0;	// 现部门数
	for(int i=0; i<MAX_D; i++)
	{
		if(d[i]->get_id() == 0)
			continue;
		else
			d_num++;
	}
	if(d_num <= 0)
	{
		cout << "无部门，删除失败" << endl;
		getch();
		return;
	}
	cout << "请输入要删除的部门编号：";
	int id = 0,index = 0;
	cin >> id;
	getch();
	for(int i=0; i<MAX_D; i++)
	{
		if(d[i]->get_id() == id)
		{
			index = i;
			break;
		}
		if(i==MAX_D-1)
		{
			cout << "无此部门，删除失败" << endl;
			getch();
			return;
		}
	}
	
	d[index] = new Department(0,"0",0);

	int count = 0;	// 该部门的员工数
	int index1[MAX_E] = {-1};	// 员工的下标
	for(int i=0; i<MAX_E; i++)
	{
		if(e[i]->get_d_id() == id)
		{
			index1[count++] = i;
		}
	}

	// 删除该部门的员工
	for(int i=0; i<count; i++)
	{	
		e[index1[i]] = new Employee(0,"0",0,0,0);	
	}
*/
	
	cout << "部门删除成功" << endl;
	getch();
	getch();
}
void ServiceImpl::listDept(void)//列出部门菜单项
{
	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);
	sprintf(cmd,"select did,name,num from Department");
	int sel = sql.select(cmd);	

	cout  << "      部门id   ";
	cout  << "      部门名   ";
	cout  << "    部门人数" << endl;
	sql.showResult();

	if(sel > 0)
	{
		cout << "输出完毕" << endl;
	}

/*
	for(int i=0; i<MAX_D; i++)
	{
		if(d[i]->get_id() != 0)
		{
			cout << "部门id：" << d[i]->get_id();
			cout << " ,部门名：" << d[i]->get_name();
			cout << " ,部门人数：" << d[i]->get_e_num() << endl;
		}	
	}
*/
	getch();
}
void ServiceImpl::addEmp(void)//增加员工菜单项
{
	cout << "请输入部门编号：";
	int d_id = 0; 
	cin >> d_id;

	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);

	sprintf(cmd,"select did from Department where did=%d",d_id);
	int sel = sql.select(cmd);
	if(sel <= 0)
	{
		cout << "sel:" << sel << endl;
		cout << "该部门不存在" << endl;
		getch();		
		return;
	}

	string name;
	int gender = 0;
	int age;
	cout << "请输入员工姓名：";
	cin >> name;
	cout << "请选择员工性别(0,表示男，1，表示女),";

	switch(get_cmd('0','1'))
	{
		case '0': gender = 0; break;
		case '1': gender = 1; break;
	}

	cout << "请输入员工年龄：";
	cin >> age;
	getch();

	sprintf(cmd,"insert into Employee VALUES(%d,'%s',%d,%d,%d)",eid++,name.c_str(),gender,age,d_id);
	int ins = sql.insert(cmd);
	if(ins <= 0)
	{
		cout << "ins:" << ins << endl;
		cout << "数据有误，插入失败" << endl;
		getch();		
		return;
	}

	sprintf(cmd,"select did from Employee where did=%d",d_id);
	int count = sql.select(cmd);
	cout << "现部门人数:" << count << endl;
	sprintf(cmd,"UPDATE Department SET num=%d where did=%d",count,d_id);
	int upd = sql.update(cmd);
	if(upd > 0)
	{
		cout << "部门数据更新完毕" << endl;
	}

/*
	// 是否存在该部门
	for(int i=0; i<MAX_D; i++)
	{
		if(d_id == d[i]->get_id())
		{
			index = i;
			break;
		}		
		if(i == MAX_D-1)
		{
			cout << "该部门不存在" << endl;
			getch();
			return;
		}
	}

	int e_num = d[index]->get_e_num();	// 现员工数
	if(e_num >= MAX_E)
	{
		cout << "员工已达上限，增加失败" << endl;
		getch();
		return;
	}
	
	string name;
	bool gender = 0;
	int age;
	cout << "请输入员工姓名：";
	cin >> name;
	cout << "请选择员工性别(0,表示男，1，表示女),";

	switch(get_cmd('0','1'))
	{
		case '0': gender = 0; break;
		case '1': gender = 1; break;
	}

	cout << "请输入员工年龄：";
	cin >> age;
	getch();
	
	for(int i=0; i<MAX_E; i++)
	{	
		if(e[i]->get_id() == 0)
		{
			e[i] = new Employee(eid++,name,gender,age,d_id);
			break;		
		}	
	}

	for(int i=0; i<MAX_D; i++)
	{	
		if(d[i]->get_id() == d_id)
		{
			int num = d[i]->get_e_num();
			d[i]->set_e_num(++num);
			break;		
		}	
	}
*/

	cout << "员工添加成功" << endl;
	getch();
}
void ServiceImpl::deleteEmp(void)//删除员工菜单项
{
	cout << "请输入员工编号:";
	int id = -1,did = -1;
	cin >> id;
	cout << "请输入员工的部门id:";
	cin >> did;
	getch();

	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);

	sprintf(cmd,"select eid from Employee where eid=%d",id);
	int sel = sql.select(cmd);
	if(sel <= 0)
	{
		cout << "sel:" << sel << endl;
		cout << "该员工不存在,删除失败" << endl;
		getch();
		return;
	}
	sprintf(cmd,"select did from Department where did=%d",did);
	int sel2 = sql.select(cmd);
	if(sel2 <= 0)
	{
		cout << "sel2:" << sel2 << endl;
		cout << "该部门不存在,删除失败" << endl;
		getch();
		return;
	}

	sprintf(cmd,"DELETE FROM Employee where eid=%d",id);
	int del = sql.remove(cmd);
	if(del <= 0)
	{
		cout << "del:" << del << endl;
		cout << "输入数据有误,删除失败" << endl;
		getch();
		return;
	}

	sprintf(cmd,"select did from Employee where did=%d",did);
	int count = sql.select(cmd);
	cout << "现部门人数:" << count << endl;
	sprintf(cmd,"UPDATE Department SET num=%d where did=%d",count,did);
	int upd = sql.update(cmd);
	if(upd > 0)
	{
		cout << "部门数据更新完毕" << endl;
	}

/*
	for(int i=0; i<MAX_E; i++)
	{
		if(id == e[i]->get_id())
		{
			index = i;
			break;
		}
		if(i == MAX_E-1)
		{
			cout << "无此员工" << endl;		
			break;
		}
	}

	e[index]->set_id(0);

	int d_id = e[index]->get_d_id();
	for(int i=0; i<MAX_D; i++)
	{
		if(d_id == d[i]->get_id())
		{
			int num = d[i]->get_e_num();
			d[i]->set_e_num(--num);
			break;
		}
		if(i == MAX_D-1)
		{
			cout << "存在脏数据，请手动修改数据" << endl;
			getch();
			return;
		}
	}
*/

	cout << "删除员工成功" << endl;
	getch();

}
void ServiceImpl::modifyEmp(void)//修改员工信息菜单项
{
	cout << "请输入员工编号:";
	int id = -1,old_did = -1;
	cin >> id;
	cout << "请输入员工的部门id:";
	cin >> old_did;
	
	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);

	sprintf(cmd,"select eid from Employee where eid=%d",id);
	int sel = sql.select(cmd);
	if(sel <= 0)
	{
		cout << "sel:" << sel << endl;
		cout << "该员工不存在,修改失败" << endl;
		getch();
		return;
	}
	sprintf(cmd,"select did from Department where did=%d",old_did);
	int sel2 = sql.select(cmd);
	if(sel2 <= 0)
	{
		cout << "sel2:" << sel2 << endl;
		cout << "该部门不存在,修改失败" << endl;
		getch();
		return;
	}

	string name;
	cout << "请输入员工的新姓名：";
	cin >> name;
	int gender = 0;
	cout << "请选择员工性别(0,表示男，1，表示女),";
	switch(get_cmd('0','1'))
	{
		case '0': gender = 0; break;
		case '1': gender = 1; break;
	}

	cout << "请输入员工的新年龄：";
	int age = 0;
	cin >> age;

	cout << "请输入员工的新部门id：";
	int did = 0;
	cin >> did;

	getch();

	sprintf(cmd,"UPDATE Employee SET name='%s',gender=%d,age=%d,did=%d where eid=%d",name.c_str(),gender,age,did,id);
	int upd = sql.update(cmd);
	if(upd <= 0)
	{
		cout << "upd:" << upd << endl;
		cout << "输入数据有误，修改失败" << endl;
		getch();
		return;
	}

	sprintf(cmd,"select did from Employee where did=%d",did);
	int count = sql.select(cmd);
	cout << "现部门人数:" << count << endl;
	sprintf(cmd,"UPDATE Department SET num=%d where did=%d",count,did);
	upd = sql.update(cmd);

/*
	for(int i=0; i<MAX_E; i++)
	{
		if(id == e[i]->get_id())
		{
			index = i;
			break;
		}
		if(i == MAX_E-1)
		{
			cout << "无此员工" << endl;		
			break;
		}
	}

	string name;
	cout << "请输入员工的新姓名：";
	cin >> name;
	bool gender = 0;
	cout << "请选择员工性别(0,表示男，1，表示女),";
	switch(get_cmd('0','1'))
	{
		case '0': gender = 0; break;
		case '1': gender = 1; break;
	}

	cout << "请输入员工的新年龄：";
	int age = 0;
	cin >> age;

	getch();

	e[index]->set_name(name);
	e[index]->set_gender(gender);
	e[index]->set_age(age);
*/

	cout << "修改成功" << endl;
	getch();
}
void ServiceImpl::listEmp(void)//列出部门员工菜单项
{
	int c_id;
	cout << "请输入部门编号:";
	cin >> c_id;
	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);
	sprintf(cmd,"select eid,name,gender,age,did from Employee where did=%d",c_id);
	int sel = sql.select(cmd);
	cout  << "      员工id   ";
	cout  << "      员工名   ";
	cout  << "性别(0男1女)   ";
	cout  << "        年龄   ";
	cout  << "      部门id" << endl;
	sql.showResult();
	if(sel > 0)
	{
		cout << "输出完毕" << endl;
	}
/*
	int c_id;
	cout << "请输入部门编号:";
	cin >> c_id;
	for(int i=0; i<MAX_E; i++)
	{
		if(e[i]->get_d_id() == c_id)
		{
			cout << "id:" << e[i]->get_id() << " ";
			cout << "name:" << e[i]->get_name() << " ";
			cout << "gender:" << e[i]->get_gender() << " ";
			cout << "age:" << e[i]->get_age() << endl;
		}
	}
*/
	cout << endl;
	getch();
	getch();
}
void ServiceImpl::listAllEmp(void)//列出所有员工菜单项
{
	SQL sql("127.0.0.1","root","root","EMIS",3306);
	char* cmd = (char*)malloc(1024);
	sprintf(cmd,"select eid,name,gender,age,did from Employee");
	int sel = sql.select(cmd);	
	cout  << "      员工id   ";
	cout  << "      员工名   ";
	cout  << "性别(0男1女)   ";
	cout  << "        年龄   ";
	cout  << "      部门id" << endl;
	sql.showResult();
	if(sel > 0)
	{
		cout << "输出完毕" << endl;
	}
/*
	for(int i=0; i<MAX_E; i++)
	{
		if(e[i]->get_id() != 0)
		{
			cout << "id:" << e[i]->get_id() << " ";
			cout << "name:" << e[i]->get_name() << " ";
			cout << "gender:" << e[i]->get_gender() << " ";
			cout << "age:" << e[i]->get_age() << " ";
			cout << "d_id:" << e[i]->get_d_id() << endl;
		}
	}
*/
	cout << endl;
	getch();
}
