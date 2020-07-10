/**
 * ְ����������ϵͳ-�ṹ������汾
 * 1.���빦��
 * 2.��ʾ����
 * 3.���ҹ���
 * 4.������
 * 5.�޸Ĺ���
 * 6.�ļ�����
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
	string id;				//Ա�����
	string name;			//Ա������
	string sex;				//Ա���Ա�
	string birthday;		//��������
	string dept;			//���ڲ���
	string title;			//ְ��
	string level;			//����
	string tel;				//�绰
};
void show_menu() {
	cout << "ְ����������ϵͳ" << endl;
	cout << "1.���ְ��" << endl;
	cout << "2.��ʾְ��" << endl;
	cout << "3.����ְ��" << endl;
	cout << "4.����" << endl;
	cout << "5.�޸�ְ��" << endl;
	cout << "6.����ְ��" << endl;
	cout << "0.�˳�" << endl;
}
bool do_add(struct Node people[], const string filename, int& len) {
	struct Node node;
	cout << "Ա�����:";
	getline(cin, node.id);
	cout << "Ա������:";
	getline(cin, node.name);
	cout << "Ա���Ա�(1:��,2:Ů):";
	string temp;
	getline(cin, temp);
	if (temp == "1") {
		node.sex = "��";
	}
	if (temp == "2") {
		node.sex = "Ů";
	}
	cout << "��������:";
	getline(cin, node.birthday);
	cout << "���ڲ���:";
	getline(cin, node.dept);
	cout << "ְ��:";
	getline(cin, node.title);
	cout << "����:";
	getline(cin, node.level);
	cout << "�绰:";
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
	printf("%10s%10s%10s%10s%10s%10s%10s%10s\n", "Ա�����", "Ա������", "Ա���Ա�", "��������", "���ڲ���", "ְ��", "����", "�绰");
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
	printf("%10s%10s%10s%10s%10s%10s%10s%10s\n", "Ա�����", "Ա������", "Ա���Ա�", "��������", "���ڲ���", "ְ��", "����", "�绰");
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
		cout << "1.����������" << endl;
		cout << "2.����Ų���" << endl;
		cout << "0.������һ��" << endl;
		getline(cin, way);
		if (way == "1") {
			cout << "����������:";
			string name;
			getline(cin, name);
			if (!search_by_name(people, length, name)) {
				cout << "δ�ҵ�" << endl;
			}
		}
		if (way == "2") {
			cout << "��������:";
			string id;
			getline(cin, id);
			if (!search_by_id(people, length, id)) {
				cout << "δ�ҵ�" << endl;
			}
		}
		if (way == "0") {
			break;
		}

	} while (true);

	return true;
}
bool do_update(struct Node people[], int length) {
	cout << "��������Ҫ���µ�Ա�����:";
	string id;
	getline(cin, id);
	if (!search_by_id(people, length, id)) {
		cout << "Ա��������" << endl;
		return false;
	}

	for (size_t i = 0; i < length; i++) {
		if (people[i].id == id) {
			string choice;
			do {
				cout << "1.�޸�����" << endl;
				cout << "2.�޸��Ա�" << endl;
				cout << "3.�޸ĳ�������" << endl;
				cout << "4.�޸Ĳ���" << endl;
				cout << "5.�޸�ְ��" << endl;
				cout << "6.�޸ļ���" << endl;
				cout << "7.�޸ĵ绰" << endl;
				cout << "0.������һ��" << endl;
				getline(cin, choice);
				if (choice == "1") {
					cout << "�������µ�����:";
					getline(cin, people[i].name);
				} else if (choice == "2") {
					cout << "�������µ��Ա�:";
					getline(cin, people[i].sex);
				} else if (choice == "3") {
					cout << "�������µĳ�������:";
					getline(cin, people[i].birthday);
				} else if (choice == "4") {
					cout << "�������µĲ���:";
					getline(cin, people[i].dept);
				} else if (choice == "5") {
					cout << "�������µ�ְ��:";
					getline(cin, people[i].title);
				} else if (choice == "6") {
					cout << "�������µļ���:";
					getline(cin, people[i].level);
				} else if (choice == "7") {
					cout << "�������µĵ绰:";
					getline(cin, people[i].tel);
				} else if (choice == "0") {
					break;
				}

			} while (true);
		}
	}

	cout << "�޸ĳɹ�" << endl;

	return false;
}
bool do_sort(struct Node people[], int length) {
	int size = length;
	bool sorted = false;            //* �տ�ʼδ����
	while (!sorted)                 //* ֱ������Ϊֹ
	{
		sorted = true;                //* �ٶ�ÿ�ζ����ź����
		for (int i = 1; i < length; i++)     //* �������εıȽ� n������Ҫ����n-1�αȽ�
		{
			if (people[i].id < people[i - 1].id)         //* �ж����ڵ��������Ĵ�С��ϵ
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

				sorted = false;       //* �н���,˵��Ϊ�������
			}
		}
		length--;                     //* ÿ���ź�һ��Ԫ��,�ݼ��Ľ�������
	}
	cout << "�����:" << endl;
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
		if (input == "1")//���ְ��
		{
			cout << "*******���ְ��*******" << endl;
			do_add(people, filename, len);
			cin.get();
			system("cls");
		} else if (input == "2")//��ʾְ��
		{
			cout << "*******��ʾְ��*******" << endl;
			do_show(people, len);
			cin.get();
			system("cls");
		} else if (input == "3")//����ְ��
		{
			cout << "*******����ְ��*******" << endl;
			do_search(people, len);
			cin.get();
			system("cls");
		} else if (input == "4")//����
		{
			cout << "*******����*******" << endl;
			do_sort(people, len);
			cin.get();
			system("cls");
		} else if (input == "5")//�޸�ְ��
		{
			cout << "*******�޸�ְ��*******" << endl;
			do_update(people, len);
			cin.get();
			system("cls");
		} else if (input == "6")//����ְ��
		{
			cout << "*******����ְ��*******" << endl;
			do_save(filename, people, len);
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