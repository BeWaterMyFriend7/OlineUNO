#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include <Windows.h>
#include"card.h"
using namespace std;

class Msg {
public:
	static void GameStart();            //��Ϸ��ʼ��ʾ
	static void CardsPlayMsg();         //���ơ����ơ�������ʾ
	static void CardsOutMsg();          //������ʾ
	static void LegalMsg();             //���ƺ��кϷ���ѡ�񣺴����������ʾ
	static void CardsColorChoice();     //��ɫ����ɫѡ����ʾ
	static void FourCardSuspectMsg();   //+4���Ƿ�ѡ��������ʾ
	static void RoundAgainMsg();        //����һ����ʾ
	static void UNOJudgeMsg();          //�Ƿ�UNO��ʾ
	static void ErrMsg();               //���������ʾ
	static void RoundOverMsg();         //��Ҹ��ֽ�����ʾ
	static void ClearMsg();             //��������
	static void HandsCards();           //����
	static void RoboCompute();			//�����˻غ����ڳ���
	static void Reverse();				//ת����ʾ��Ϣ
	static void Allcolor();				//תɫ��ʾ��Ϣ
	static void PrintCard(Card &card);	//��ӡֽ����Ϣ
};

class GameMenu {
public:
	void Show_menu();

	bool Menumain();

};



//void Show_rank() {
//	ifstream show_rank;
//	show_rank.open("rank.txt", ios::in);
//	if (!show_rank.is_open())
//	{
//		cout << "Fail to open this rank menu.Please make sure that you have finished 1 game at least!" << endl;
//	}
//	char grade_message[1024] = {0};
//	while (show_rank.getline(grade_message, sizeof(grade_message)))
//	{
//		cout << grade_message << endl;
//	}
//}


