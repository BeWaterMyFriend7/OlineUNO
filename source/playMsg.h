#pragma once
#include <iostream>
#include "COLOR.h"
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
};
