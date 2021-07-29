#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<string.h>
#include<ctime>
#include"card.h"
using namespace std;


class Robo  {
public:
	Robo();
	void RoboInit(Card preCard, int numnext, int nextplayer, vector<vector<string>> colorLack); //��ʼ��


	vector<int> cardNumHigher3(vector<Card> &vaildCards);	//������������ʱ���ȼ���������ʱ�Ϸ���Ӧ�����ƣ�����Ϸ��ƣ�������Ʒ���
	vector<int> cardNumNotHigher3(vector<Card> &vaildCards);			//���ڻ������������ʱ���ȼ���������ʱ�Ϸ���Ӧ�����ƣ�����Ϸ��ƣ�������Ʒ���
	vector<Card> getPlayerVaildCard(vector<Card> &playerCards); //�õ���Ч���ƶѣ�6/11�¼ӣ�
	map<int, string> getColorRobo(vector<Card> &playerCards);		//�õ���ǰ������������ɫͳ��
	
	Card cardOut(vector<int> &cardPoint,vector<Card> &vaildCards);           //��������ƣ���Ҫ�������������ȼ�vector����
	string cardOutColor(Card &card, map<int, string> &colorRobo);					//�����ɫ����������˴����ɫ�ƣ���Ҫȷ����ɫ
	//bool isQusetion(Card &preCard);							//�Ƿ�������һ�����,��������һ���������
	Card computerReact(vector<Card> &playerCards);			//�������ƶѣ�����һ���ƣ�6/11�¼ӣ�������
	int cardPosition(vector<Card> &playerCards, Card &outCard);	//����������������player�е�λ��

	bool roboOutMain(vector<Card> &playerCards,bool &isQusePrePlayer, bool &isPickCard, Card &nowCard);		//��������ģ�飬��Ҫ�ж��Ƿ���Ҫ����,�����Ƿ����ƵĲ���ֵ

	vector<Card> playerCards;
	Card preCard;									//��Ҫȷ���Ƿ�������������ڱ���࣬����ͨ���β�ʵ��
	int numNext;									//��һ�������ʣ��������
	int nextPlayer;									//��һ����ң�next_player��һ�����֣�������Ϊ�Ǿ��뿪���˵ľ��� ᯸����һ��ָ����һ����ҵĵ����� ����������������ȷ���Ƿ��������ȿ��Ե��βΣ�Ҳ���Է�������½�һ�����캯��
	vector<vector<string>> colorLack;

	Card nowCard;									//��ǰ����
	vector<Card> vaildCards;						//��ǰ��ҺϷ����ƶ�
	map<int, string> colorRobo;						//��ǰ���������Ƶ���ɫͳ�� ���� R G B Y
};
