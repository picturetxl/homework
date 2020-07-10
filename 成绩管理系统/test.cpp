#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#define MAXNUM 50
using namespace std;

struct Node {
	string sid;				//ѧ��
	string name;			//����
	string cid;				//�γ̱��
	string coursename;		//�γ�����
	unsigned int score;		//�ɼ�
	double xuefen;			//ѧ��
};
void show_menu() {
	cout << "�ɼ���¼��" << endl;
	cout << "1.���" << endl;
	cout << "2.ɾ��" << endl;
	cout << "3.��ѧ���ɼ�" << endl;
	cout << "4.���ɼ���" << endl;
	cout << "5.д���ļ�" << endl;
	cout << "6.��ȡ�ļ�" << endl;
	cout << "0.�˳�" << endl;
}
void show_node(struct Node node) {
	printf("%10s%10s%10s%10s%10s%10s\n", "ѧ��", "����", "�γ̱��", "�γ�����", "�ɼ�", "ѧ��");
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
		cout << "�ļ���û������" << endl;
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
	
	printf("%10s%10s%10s%10s%10s%10s\n", "ѧ��", "����", "�γ̱��", "�γ�����", "�ɼ�", "ѧ��");
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
		cout << "ѧ��:";
		getline(cin, sid);//8λ����
		if (sid.size() == 8 && is_num(sid,8)) {
			node.sid = sid;
			break;
		}
		else {
			cout << "��Ч,8λ����" << endl;
		}
	} while (true);
	
	cout << "����:";
	getline(cin, node.name);
	do {
		string cid; 
		cout << "�γ̱��:";
		getline(cin, cid);//5λ����
		if (cid.size() == 5 && is_num(cid,5)) {
			node.cid = cid;
			break;
		} else {
			cout << "��Ч,5λ����" << endl;
		}
	} while (true);
	
	cout << "�γ�����:";
	getline(cin, node.coursename);

	do {
		cout << "�ɼ�:";
		string score;
		getline(cin, score);//0-100 
		int input_score = stod(score);
		if (input_score >= 0 && input_score <= 100) {
			node.score = input_score;
			break;
		}
		else {
			cout << "��Ч,������0-100" << endl;
		}
	} while (true);
	

	do {

		cout << "ѧ��:";
		string xuefen;
		getline(cin, xuefen);//1-5
		double xf = stod(xuefen);
		if (xf >= 1 && xf <= 5) {
			node.xuefen = stod(xuefen);
			break;
		} else {
			cout << "��Ч,1-5" << endl;
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
	cout << "��������Ҫ���ҵ�ѧ����ѧ��:";
	string sid;
	getline(cin, sid);
	double total_xuefen = 0;
	bool flag = false;
	printf("%10s%10s%10s%10s%10s%10s\n", "ѧ��", "����", "�γ̱��", "�γ�����", "�ɼ�", "ѧ��");
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
		cout << "û�ҵ�" << endl;
		return;
	}
	else {
		cout << "ѧ��:" << sid << " �����ѧ��:" << total_xuefen << endl;
	}
	
}
void do_search_class(struct Node people[], int length) {
	cout << "��������Ҫ���ҿγ̺�:";
	string cid;
	getline(cin, cid);
	double sum = 0;//�ܷ�
	double jgl=0;//������
	double jg_ren=0;//��������
	double total=0;//������
	bool flag = false;
	printf("%10s%10s%10s%10s%10s%10s\n", "ѧ��", "����", "�γ̱��", "�γ�����", "�ɼ�", "ѧ��");
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
		cout << "û�ҵ�" << endl;
		return;
	}
	else {
		cout << "ƽ����:" << sum / total << endl;
		cout << "������:" << jg_ren / total *100.0<< "%"<<endl;

	}

}
void do_delete(struct Node people[], int& length) {
	cout << "��������Ҫɾ��ѧ����ѧ��:";
	string sid;
	getline(cin, sid);
	cout << "��������Ҫɾ��ѧ���Ŀγ̺�:";
	string cid;
	getline(cin, cid);
	int index = search_course(people,length,sid,cid);
	if (index == -1) {
		cout << "������,����������" << endl;
	} else {
		cout << "����ɾ����¼..." << endl;
		//show_node(people[index]);
		for (int i = index; i < length; i++) {
			people[i] = people[i + 1];
		}
		length--;
		cout << "ɾ�����" << endl;
	}
}
int main() {
	//0.��������ͱ����ļ�
	struct Node people[MAXNUM];
	string filename = "data.txt";
	//��ʼ������
	int len = 0;
	do_init(people, filename, len);
	//1.�û��˵�
	string choice;
	do {
		//��ʾ�˵�
		show_menu();
		string input;
		getline(cin, input);
		if (input == "1")//���
		{
			cout << "*******���*******" << endl;
			do_add(people, filename, len);
			
			cin.get();
			system("cls");
		} else if (input == "2")//ɾ��
		{
			cout << "*******ɾ��*******" << endl;
			do_delete(people, len);
			do_save(filename,people,len);
			cin.get();
			system("cls");
		} else if (input == "3")//��ѧ���ɼ�
		{
			cout << "*******��ѧ���ɼ�*******" << endl;
			do_search_score(people, len);
			cin.get();
			system("cls");
		} else if (input == "4")//���ɼ���
		{
			cout << "*******���ɼ���*******" << endl;
			do_search_class(people, len);
			cin.get();
			system("cls");
		} else if (input == "5")//д���ļ�
		{
			cout << "*******д���ļ�*******" << endl;
			do_save(filename,people, len);
			cin.get();
			system("cls");
		} else if (input == "6")//��ȡ�ļ�
		{
			cout << "*******��ȡ�ļ�*******" << endl;
			do_read(filename, people, len);
			cin.get();
			system("cls");
		} else if (input == "0")//quit
		{
			cout << "��ӭ�´�ʹ��" << endl;
			break;
		}
	} while (true);

	cout << "helloworld" << endl;

	return 0;
}

