#include "manager.h"

Manager::Manager()
{
	this->initUserdata();
	v1.resize(10000);
}

void Manager::show_style()
{
	system("color f0");
	system("UNO��Ϸ");
	system("mode con cols=100 lines=35"); //conΪ����̨
}

void Manager::show_welcome()
{
	cout << "**********��ӭ����UNO��Ϸ**********\t" << endl;
	cout << endl << "**************1.ע��**************\t" << endl;
	cout << "**************2.��¼**************\t" << endl;
	cout << "**************3.�˳�**************\t" << endl;
	cout << endl;
}
void Manager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void Manager::login()
{
	string name, password;
	char tempusernum[10];
	user u1;
	ifstream iofs1;
	ifstream iofs2;
flag:
	iofs1.open("resource/userdata.txt", ios::in);
	iofs2.open("resource/usernum.txt", ios::in);
	cout << "�������˺�" << endl;
	cout << "�˺�Ӧ��Ϊ4-10λ��Ӣ����ĸ" << endl;
	if (!iofs1.is_open() || !iofs2.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	else
	{
		iofs2.getline(tempusernum, sizeof(tempusernum));
		usernum = atoi(tempusernum);
		if (usernum != 0)
		{
			int p = usernum, point1 = 0;
			while (p > 0)
			{
				getline(iofs1, v1[point1].name);
				getline(iofs1, v1[point1].password);
				point1++;
				p--;
			}
			iofs1.close();
			iofs2.close();
		}
	}
	cin >> name;
	if (name >= "AAAA" && name <= "zzzzzzzzzz" && name.length() >= 4 && name.length() <= 10)
	{
		if (usernum > 0)
		{
			for (int i = 0; i < usernum; i++)
			{
				if (v1[i].name == name)
				{
					cout << "�˺��Ѵ���!" << endl;
					system("pause");
					system("cls");
					return;
				}
			}
			cout << "����������" << endl;
			cout << "���볤��Ӧ���ڵ�����λ" << endl;
			cin >> password;
			if (password.length() < 6)
			{
				cout << "���볤�ȷǷ�" << endl;
				system("pause");
				system("cls");
				goto flag;
			}
		}
		else
		{
			cout << "����������" << endl;
			cout << "���볤��Ӧ���ڵ�����λ" << endl;
			cin >> password;
			if (password.length() < 6)
			{
				cout << "���볤�ȷǷ�" << endl;
				system("pause");
				system("cls");
				goto flag;
			}
		}
	}
	else
	{
		cout << "����������Ϸ��˺�" << endl;
		goto flag;
	}
	fstream iofs3;
	fstream iofs4;
	iofs3.open("resource/userdata.txt", ios::out | ios::app);
	iofs4.open("resource/usernum.txt", ios::out);
	iofs4 << ++usernum << endl;
	iofs3 << name << endl;
	iofs3 << password << endl;
	iofs3.close();
	iofs4.close();
	cout << "��ϲע��ɹ�" << endl;
	system("pause");
	system("cls");
}

void Manager::enroll()				//��¼
{
	string name, password, tempPassword;
	user u1;
	char tempusernum[10];
	cout << "�������˺�" << endl;
	ifstream iofs1;
	ifstream iofs2;
	iofs1.open("resource/userdata.txt", ios::in);
	iofs2.open("resource/usernum.txt", ios::in);
	if (!iofs1.is_open() || !iofs2.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	else
	{
		iofs2.getline(tempusernum, sizeof(tempusernum));
		usernum = atoi(tempusernum);
		if (usernum != 0)
		{
			int p = usernum, point1 = 0;
			while (p > 0)
			{
				getline(iofs1, v1[point1].name);
				getline(iofs1, v1[point1].password);
				point1++;
				p--;
			}
		}
	}
	iofs1.close();
	iofs2.close();
	cin >> name;
	if (name >= "AAAA" && name <= "zzzzzzzzzz" && name.length() >= 4 && name.length() <= 10)
	{
		if (usernum > 0)
		{
			bool flag = 0;
			for (int i = 0; i < usernum; i++)
			{
				if (v1[i].name == name)
				{
					tempPassword = v1[i].password;
					cout << "����������" << endl;
					cin >> password;
					flag = 1;
				}
			}
			if (flag == 0)
			{
				cout << "�˺Ų�����" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		else
		{
			cout << "�˺Ų�����" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	else
	{
		cout << "�˺Ų�����" << endl;
		system("pause");
		system("cls");
		return;
	}
	if (password == tempPassword)
	{
		cout << "��½�ɹ�" << endl;
		cout << "��Ϸ������ʼ" << endl;
		system("pause");
		system("color fa");
		system("mode con cols=120 lines=40");
	}
	else
	{
		cout << "�������" << endl;
		system("pause");
		system("cls");
		return;
	}
}
void Manager::initUserdata()
{
	this->v1.clear();
}


bool Manager::managerMain() {
	system("resource/voice.vbs");
	this->show_style();
	string choice;
	while (true)
	{
		this->show_welcome();
		cout << "************����ѡ����************\t" << endl;
		cin >> choice;
		if (choice.length() != 1)
		{
			cout << "��Ч���룬����������" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			switch (choice[0])
			{
			case '1':
				this->login();
				break;
			case '2':
				this->enroll();
				return true;
				break;

			case '3':
				this->exitSystem();
			default:
				cout << "��Ч���룬����������" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
	}
	return false;
}

void Manager::operaterpush_back(vector<user>& v) {

}

Manager::~Manager()
{

}