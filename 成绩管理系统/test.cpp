#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#define MAXNUM 50
using namespace std;

struct Node {
	string sid;				//学号
	string name;			//姓名
	string cid;				//课程编号
	string coursename;		//课程名称
	unsigned int score;		//成绩
	double xuefen;			//学分
};
void show_menu() {
	cout << "成绩记录簿" << endl;
	cout << "1.添加" << endl;
	cout << "2.删除" << endl;
	cout << "3.查学生成绩" << endl;
	cout << "4.查班成绩表" << endl;
	cout << "5.写入文件" << endl;
	cout << "6.读取文件" << endl;
	cout << "0.退出" << endl;
}
void show_node(struct Node node) {
	printf("%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "课程编号", "课程名称", "成绩", "学分");
	cout << setw(10) << node.sid;
	cout << setw(10) << node.name;
	cout << setw(10) << node.cid;
	cout << setw(10) << node.coursename;
	cout << setw(10) << node.score;
	cout << setw(10) << node.xuefen;
	cout << endl;
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
		is >> people[len].sid;
		is >> people[len].name;
		is >> people[len].cid;
		is >> people[len].coursename;
		string score;
		is >> score;
		people[len].score = stod(score);
		string xuefen;
		is >> xuefen;
		people[len].xuefen = stod(xuefen);
		len++;
	}
	if (len == 0) {
		cout << "文件中没有数据" << endl;
	}
}
void do_read(string filename,struct Node people[],int& len) {
	ifstream readfile;
	readfile.open(filename);
	if (!readfile) {
		cout << "file can not open" << endl;
		exit(EXIT_FAILURE);
	}
	string query;
	
	printf("%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "课程编号", "课程名称", "成绩", "学分");
	while (getline(readfile, query)) {
		struct Node node;
		std::istringstream is(query);
		is >> node.sid;
		is >> node.name;
		is >> node.cid;
		is >> node.coursename;
		string score;
		is >> score;
		node.score = (int)stod(score);
		string xuefen;
		is >> xuefen;
		node.xuefen = stod(xuefen);
		cout << setw(10) << node.sid;
		cout << setw(10) << node.name;
		cout << setw(10) << node.cid;
		cout << setw(10) << node.coursename;
		cout << setw(10) << node.score;
		cout << setw(10) << node.xuefen;
		cout << endl;
	}
	readfile.close();
}
bool do_save(string filename, struct Node people[], int length) {
	ofstream out;
	out.open(filename);
	for (size_t i = 0; i < length; i++) {
		out << people[i].sid << "\t"
			<< people[i].name << "\t"
			<< people[i].cid << "\t"
			<< people[i].coursename << "\t"
			<< people[i].score << "\t"
			<< people[i].xuefen << endl;
	}
	out.close();
	return true;
}
bool is_num(string s,int len) {
	for (int i = 0; i <len; i++) {
		if (!isalnum(s[i])) {
			return false;
		}
	}
	return true;
}
bool do_add(struct Node people[], const string filename, int& len) {
	struct Node node;
	
	do {
		string sid;
		cout << "学号:";
		getline(cin, sid);//8位数字
		if (sid.size() == 8 && is_num(sid,8)) {
			node.sid = sid;
			break;
		}
		else {
			cout << "无效,8位数字" << endl;
		}
	} while (true);
	
	cout << "姓名:";
	getline(cin, node.name);
	do {
		string cid; 
		cout << "课程编号:";
		getline(cin, cid);//5位数字
		if (cid.size() == 5 && is_num(cid,5)) {
			node.cid = cid;
			break;
		} else {
			cout << "无效,5位数字" << endl;
		}
	} while (true);
	
	cout << "课程名称:";
	getline(cin, node.coursename);

	do {
		cout << "成绩:";
		string score;
		getline(cin, score);//0-100 
		int input_score = stod(score);
		if (input_score >= 0 && input_score <= 100) {
			node.score = input_score;
			break;
		}
		else {
			cout << "无效,请输入0-100" << endl;
		}
	} while (true);
	

	do {

		cout << "学分:";
		string xuefen;
		getline(cin, xuefen);//1-5
		double xf = stod(xuefen);
		if (xf >= 1 && xf <= 5) {
			node.xuefen = stod(xuefen);
			break;
		} else {
			cout << "无效,1-5" << endl;
		}

	} while (true);

	
	people[len] = node;
	len++;
	do_save(filename, people, len);
	return true;
}
int search_course(struct Node people[], int length, string sid,string cid) {
	bool find_flag = false;
	for (size_t i = 0; i < length; i++) {
		if (people[i].sid == sid && people[i].cid== cid) {
			show_node(people[i]);
			return i;
		}
	}
	return -1;
}
void do_search_score(struct Node people[], int length) {
	cout << "请输入需要查找的学生的学号:";
	string sid;
	getline(cin, sid);
	double total_xuefen = 0;
	bool flag = false;
	printf("%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "课程编号", "课程名称", "成绩", "学分");
	for (size_t i = 0; i < length; i++) {
		if (people[i].sid == sid ) {
			flag = true;
			cout << setw(10) << people[i].sid;
			cout << setw(10) << people[i].name;
			cout << setw(10) << people[i].cid;
			cout << setw(10) << people[i].coursename;
			cout << setw(10) << people[i].score;
			cout << setw(10) << people[i].xuefen;
			cout << endl;
			total_xuefen += people[i].xuefen;
		}
	}
	if (!flag) {
		cout << "没找到" << endl;
		return;
	}
	else {
		cout << "学生:" << sid << " 共获得学分:" << total_xuefen << endl;
	}
	
}
void do_search_class(struct Node people[], int length) {
	cout << "请输入需要查找课程号:";
	string cid;
	getline(cin, cid);
	double sum = 0;//总分
	double jgl=0;//及格率
	double jg_ren=0;//及格人数
	double total=0;//总人数
	bool flag = false;
	printf("%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "课程编号", "课程名称", "成绩", "学分");
	for (size_t i = 0; i < length; i++) {
		if (people[i].cid == cid) {
			flag = true;
			cout << setw(10) << people[i].sid;
			cout << setw(10) << people[i].name;
			cout << setw(10) << people[i].cid;
			cout << setw(10) << people[i].coursename;
			cout << setw(10) << people[i].score;
			cout << setw(10) << people[i].xuefen;
			cout << endl;
			sum+= people[i].score;
			if (people[i].score >= 60) {
				jg_ren++;
			}
			total++;
		}
	}
	if (!flag) {
		cout << "没找到" << endl;
		return;
	}
	else {
		cout << "平均分:" << sum / total << endl;
		cout << "及格率:" << jg_ren / total *100.0<< "%"<<endl;

	}

}
void do_delete(struct Node people[], int& length) {
	cout << "请输入需要删除学生的学号:";
	string sid;
	getline(cin, sid);
	cout << "请输入需要删除学生的课程号:";
	string cid;
	getline(cin, cid);
	int index = search_course(people,length,sid,cid);
	if (index == -1) {
		cout << "不存在,请重新输入" << endl;
	} else {
		cout << "正在删除记录..." << endl;
		//show_node(people[index]);
		for (int i = index; i < length; i++) {
			people[i] = people[i + 1];
		}
		length--;
		cout << "删除完成" << endl;
	}
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
		if (input == "1")//添加
		{
			cout << "*******添加*******" << endl;
			do_add(people, filename, len);
			
			cin.get();
			system("cls");
		} else if (input == "2")//删除
		{
			cout << "*******删除*******" << endl;
			do_delete(people, len);
			do_save(filename,people,len);
			cin.get();
			system("cls");
		} else if (input == "3")//查学生成绩
		{
			cout << "*******查学生成绩*******" << endl;
			do_search_score(people, len);
			cin.get();
			system("cls");
		} else if (input == "4")//查班成绩表
		{
			cout << "*******查班成绩表*******" << endl;
			do_search_class(people, len);
			cin.get();
			system("cls");
		} else if (input == "5")//写入文件
		{
			cout << "*******写入文件*******" << endl;
			do_save(filename,people, len);
			cin.get();
			system("cls");
		} else if (input == "6")//读取文件
		{
			cout << "*******读取文件*******" << endl;
			do_read(filename, people, len);
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

