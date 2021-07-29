#pragma once
#include <cstdlib>
#include "time.h"
#include"manager.h"
#include "player.h"
#include "card.h"
#include "deck.h"
#include "robo.h"
#include"gamemenu.h"
#include "string.h"
#include "Context.h"				//����ͼ��
#include <vector>

class Process {
public:
	Player currentPlayer;
	Player lastPlayer;				//Player���ṩ��¼��ǰ���ӵ�е��Ƶ����ݽṹ,�ṩadd��del��������addһ������������Card������Ϊ��������������ݽṹ���޸ģ����⻹Ӧ���ṩһ����ʼ���������Ա���ÿ�ֿ�ʼʱ��Player�ڵ���������ʼ��
	Deck deck;						//��Ҫһ��Draw��������ɳ��Ʋ���ɾ���ƶ��еĸ��ƣ�����鲻���ƾͷ���һ��0����Ҫһ��remains��int������ʾʣ������,��Ҫһ��init��������ɶ��ƶѵĳ�ʼ�����Ա���ÿ�����¿�ʼ��Ϸ
	Card pPreCard;					//Card��Ҫ�ṩfunction����ʾ���ֻ��߹��ܣ��ṩcolor��ʾ��ɫ��Card��==����Ӧ�ж���������ȫ��ͬ
	Card preCard;
	Card currentCard;
	Card receiveCard;				//���յĵ����� �ϼ�  ���ϼҵ���
	vector<Player> players;			//��ʼ��һ��������飬��¼��������ң�����0�������������ң������ǻ������
	int currentPos;		//��ʾ��ǰ��Ϸ��˭�Ļغ�
	int countNum;		//���ɵļ�������
	int direction;
	bool flag;		//������Ϸ��������
	
	bool flagEnd = false; //������Ϸ�Ƿ����
	bool flagfirst = true;//�Ƿ��ǵ�һ�ֱ���
	string colorSelect;			//תɫʱ����ɫѡ��
	bool flagPlusCard = true;	//�Ƿ�����
	Robo robo;
	vector<vector<string>> lackColor;
	
	GameMenu unoMenu;			//���˵���ʾ
	Msg unoMsg;					//cmd��ʾ��Ϣ
	
	Process();
	void initDeck();			//��ʼ���ƿ�����
	void initLackColor();
	void startUNO();

	bool start();										//��������->ע���¼->��ʼ��Ϸ�������ɹ�����1������ʧ�ܷ���0
	bool execute();
	

	void playStageFirst();									//��һ����Ϸ
	void playStageNotFirst();								//�ǵ�һ����Ϸ
	void updateCard();										//���� ���ϸ���ҳ��� �ϸ���ҳ��� ��ǰ���� �ͽ��ճ���
	void updatePos(int & pos, int flag = 0);					//���µ�ǰ���λ��
	void roboAndPlayer(vector<Player>::iterator &it);		//���ƽ׶λ����˺���ҵĳ���ʵ��  ����ָ��ǰ��ҵĵ�����
	void updateReceiveColor();								//����漰��תɫ��Ҫ��received ��color��Ϊ��Ӧ��ɫ����������Ϸ����ɫ
	void recordPlayerColor();								//��¼������ҿ���ȱ�ٵ��ƻ�ɫ��
};
