/**
 * 职工档案管理系统-结构体数组版本
 * 1.输入功能
 * 2.显示功能
 * 3.查找功能
 * 4.排序功能
 * 5.修改功能
 * 6.文件保存
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#define MAXNUM 50
using namespace std;

struct Node {
	string id;				//员工编号
	string name;			//员工姓名
	string sex;				//员工性别
	string birthday;		//出生日期
	string dept;			//所在部门
	string title;			//职称
	string level;			//级别
	string tel;				//电话
};
void show_menu() {
	cout << "职工档案管理系统" << endl;
	cout << "1.添加职工" << endl;
	cout << "2.显示职工" << endl;
	cout << "3.查找职工" << endl;
	cout << "4.排序" << endl;
	cout << "5.修改职工" << endl;
	cout << "6.保存职工" << endl;
	cout << "0.退出" << endl;
}
bool do_add(struct Node people[], const string filename, int& len) {
	struct Node node;
	cout << "员工编号:";
	getline(cin, node.id);
	cout << "员工姓名:";
	getline(cin, node.name);
	cout << "员工性别(1:男,2:女):";
	string temp;
	getline(cin, temp);
	if (temp == "1") {
		node.sex = "男";
	}
	if (temp == "2") {
		node.sex = "女";
	}
	cout << "出生日期:";
	getline(cin, node.birthday);
	cout << "所在部门:";
	getline(cin, node.dept);
	cout << "职称:";
	getline(cin, node.title);
	cout << "级别:";
	getline(cin, node.level);
	cout << "电话:";
	getline(cin, node.tel);
	people[len] = node;
	len++;
	return true;
}
void do_init(struct Node people[], const string filename, int& len) {
	ifstream readfile;
	readfile.open(filename);
	if (!readfile) {
		cout << "file can not open" << endl;
		exit(EXIT_FAILURE);
	}
	string query;
	while (getline(readfile, query)) {
		std::istringstream is(query);
		is >> people[len].id;
		is >> people[len].name;
		is >> people[len].sex;
		is >> people[len].birthday;
		is >> people[len].dept;
		is >> people[len].title;
		is >> people[len].level;
		is >> people[len].tel;

		len++;
	}
}
void do_show(struct Node people[], int length) {
	printf("%10s%10s%10s%10s%10s%10s%10s%10s\n", "员工编号", "员工姓名", "员工性别", "出生日期", "所在部门", "职称", "级别", "电话");
	for (size_t i = 0; i < length; i++) {
		string sex;
		cout << setw(10) << people[i].id;
		cout << setw(10) << people[i].name;
		cout << setw(10) << people[i].sex;
		cout << setw(10) << people[i].birthday;
		cout << setw(10) << people[i].dept;
		cout << setw(10) << people[i].title;
		cout << setw(10) << people[i].level;
		cout << setw(10) << people[i].tel;
		cout << endl;
	}
}
void show_node(struct Node node) {
	printf("%10s%10s%10s%10s%10s%10s%10s%10s\n", "员工编号", "员工姓名", "员工性别", "出生日期", "所在部门", "职称", "级别", "电话");
	cout << setw(10) << node.id;
	cout << setw(10) << node.name;
	cout << setw(10) << node.sex;
	cout << setw(10) << node.birthday;
	cout << setw(10) << node.dept;
	cout << setw(10) << node.title;
	cout << setw(10) << node.level;
	cout << setw(10) << node.tel;
	cout << endl;
}
bool search_by_id(struct Node people[], int length, string id) {
	bool find_flag = false;
	for (size_t i = 0; i < length; i++) {
		if (people[i].id == id) {
			show_node(people[i]);
			return true;
		}
	}
	return false;
}
bool search_by_name(struct Node people[], int length, string name) {
	bool find_flag = false;
	for (size_t i = 0; i < length; i++) {
		if (people[i].name == name) {
			show_node(people[i]);
			return true;
		}
	}
	return false;
}
bool do_search(struct Node people[], int length) {

	do {
		string way;
		cout << "1.按姓名查找" << endl;
		cout << "2.按编号查找" << endl;
		cout << "0.返回上一级" << endl;
		getline(cin, way);
		if (way == "1") {
			cout << "请输入姓名:";
			string name;
			getline(cin, name);
			if (!search_by_name(people, length, name)) {
				cout << "未找到" << endl;
			}
		}
		if (way == "2") {
			cout << "请输入编号:";
			string id;
			getline(cin, id);
			if (!search_by_id(people, length, id)) {
				cout << "未找到" << endl;
			}
		}
		if (way == "0") {
			break;
		}

	} while (true);

	return true;
}
bool do_update(struct Node people[], int length) {
	cout << "请输入你要更新的员工编号:";
	string id;
	getline(cin, id);
	if (!search_by_id(people, length, id)) {
		cout << "员工不存在" << endl;
		return false;
	}

	for (size_t i = 0; i < length; i++) {
		if (people[i].id == id) {
			string choice;
			do {
				cout << "1.修改姓名" << endl;
				cout << "2.修改性别" << endl;
				cout << "3.修改出生年月" << endl;
				cout << "4.修改部门" << endl;
				cout << "5.修改职称" << endl;
				cout << "6.修改级别" << endl;
				cout << "7.修改电话" << endl;
				cout << "0.返回上一级" << endl;
				getline(cin, choice);
				if (choice == "1") {
					cout << "请输入新的姓名:";
					getline(cin, people[i].name);
				} else if (choice == "2") {
					cout << "请输入新的性别:";
					getline(cin, people[i].sex);
				} else if (choice == "3") {
					cout << "请输入新的出生年月:";
					getline(cin, people[i].birthday);
				} else if (choice == "4") {
					cout << "请输入新的部门:";
					getline(cin, people[i].dept);
				} else if (choice == "5") {
					cout << "请输入新的职称:";
					getline(cin, people[i].title);
				} else if (choice == "6") {
					cout << "请输入新的级别:";
					getline(cin, people[i].level);
				} else if (choice == "7") {
					cout << "请输入新的电话:";
					getline(cin, people[i].tel);
				} else if (choice == "0") {
					break;
				}

			} while (true);
		}
	}

	cout << "修改成功" << endl;

	return false;
}
bool do_sort(struct Node people[], int length) {
	int size = length;
	bool sorted = false;            //* 刚开始未排序
	while (!sorted)                 //* 直到排序为止
	{
		sorted = true;                //* 假定每次都是排好序的
		for (int i = 1; i < length; i++)     //* 进行依次的比较 n个数需要进行n-1次比较
		{
			if (people[i].id < people[i - 1].id)         //* 判断相邻的两个数的大小关系
			{
				struct Node temp;
				temp.id = people[i].id;
				temp.name = people[i].name;
				temp.sex = people[i].sex;
				temp.birthday = people[i].birthday;
				temp.dept = people[i].dept;
				temp.title = people[i].title;
				temp.level = people[i].level;
				temp.tel = people[i].tel;

				people[i].id = people[i - 1].id;
				people[i].name = people[i - 1].name;
				people[i].sex = people[i - 1].sex;
				people[i].birthday = people[i - 1].birthday;
				people[i].dept = people[i - 1].dept;
				people[i].title = people[i - 1].title;
				people[i].level = people[i - 1].level;
				people[i].tel = people[i - 1].tel;

				people[i - 1].id = temp.id;
				people[i - 1].name = temp.name;
				people[i - 1].sex = temp.sex;
				people[i - 1].birthday = temp.birthday;
				people[i - 1].dept = temp.dept;
				people[i - 1].title = temp.title;
				people[i - 1].level = temp.level;
				people[i - 1].tel = temp.tel;

				sorted = false;       //* 有交换,说明为完成排序
			}
		}
		length--;                     //* 每次排好一个元素,递减的进行排序
	}
	cout << "排序后:" << endl;
	do_show(people, size);
	return true;
}
bool do_save(string filename, struct Node people[], int length) {
	ofstream out;
	out.open(filename);
	for (size_t i = 0; i < length; i++) {
		out << people[i].id << "\t"
			<< people[i].name << "\t"
			<< people[i].sex << "\t"
			<< people[i].birthday << "\t"
			<< people[i].dept << "\t"
			<< people[i].title << "\t"
			<< people[i].level << "\t"
			<< people[i].tel << endl;
	}
	out.close();
	return true;
}
int main() {
	//0.建立数组和保存文件
	struct Node people[MAXNUM];
	string filename = "data.txt";
	//初始化数组
	int len = 0;
	do_init(people, filename, len);
	//1.用户菜单
	string choice;
	do {
		//显示菜单
		show_menu();
		string input;
		getline(cin, input);
		if (input == "1")//添加职工
		{
			cout << "*******添加职工*******" << endl;
			do_add(people, filename, len);
			cin.get();
			system("cls");
		} else if (input == "2")//显示职工
		{
			cout << "*******显示职工*******" << endl;
			do_show(people, len);
			cin.get();
			system("cls");
		} else if (input == "3")//查找职工
		{
			cout << "*******查找职工*******" << endl;
			do_search(people, len);
			cin.get();
			system("cls");
		} else if (input == "4")//排序
		{
			cout << "*******排序*******" << endl;
			do_sort(people, len);
			cin.get();
			system("cls");
		} else if (input == "5")//修改职工
		{
			cout << "*******修改职工*******" << endl;
			do_update(people, len);
			cin.get();
			system("cls");
		} else if (input == "6")//保存职工
		{
			cout << "*******保存职工*******" << endl;
			do_save(filename, people, len);
			cin.get();
			system("cls");
		} else if (input == "0")//quit
		{
			cout << "欢迎下次使用" << endl;
			break;
		}
	} while (true);

	cout << "helloworld" << endl;

	return 0;
}