#include <iostream>
#include "process.h"
#include <algorithm>
#include <windows.h>
using namespace std;

//�Ƿ���������
bool is_NumCard(Card& card) {
	if (card.number >= 0 && card.number <= 9) return 1;
	return 0;
}

//�Ϸ����ж�
bool cardJudge(Card &receiveCard, Card &currentCard) {
	if (currentCard.number == 13 || currentCard.number == 14) {
		return true;
	}
	if (currentCard.color == receiveCard.color || currentCard.number == receiveCard.number)
		return true;
	return false;
}

//��ö������ת��Ϊ�ַ���
string enumToString(int color) {
	switch (color)
	{
	case red:
		return "red";
		break;
	case green:
		return "green";
	case blue:
		return "blue";
	case yellow:
		return "yellow";
	case black:
		return "black";
	default:
		break;
	}
}


Process::Process(){

}

//��ʼ���ƿ�
void Process::initDeck() {

}


//��ʼ��Ϸ���֣��ƿ��ʼ������ҳ�ʼ��������ȷ������ʼ�����ֲ���
void Process::startUNO() {
	unoMsg.GameStart();
	deck.Init();		//�ƿ��ʼ��
	deck.Shuffle();		//�ƿ�ϴ��

	for (int i = 0; i < 4; i++) { //��ʼ�����
		Player p;
		players.push_back(p);
	}

	Context ct;
	//Context ct = Context(Draw("interface_Begin"));
	ct.show();

	for (vector<Player>::iterator it = players.begin(); it != players.end(); it++) {
		for (int i = 0; i < 7; i++) {
			it->handCardAdd(deck.getCard());
		}
	}
	while (true)
	{
		receiveCard = deck.getCard();		//����
		if (receiveCard.number == 14 || receiveCard.number == 13) {			//���Լ�Ϊ.color����
			deck.addCard(receiveCard);		//��������Ǻ�ɫ�ƣ������ƷŻ�
		}
		else {
			break;							//���Ʋ��Ǻ�ɫ�ƣ���ɲ���
		}
	}

	preCard = receiveCard;
	//deck.addCard(receiveCard);			//�˴�ȷ���ƿⲻ�䣬���ó�ʼ��һ�������Ϣ
	currentPos = 0;//(int)rand() % 4;	//���ѡ��һ�������Ϊ��ʼ��ҳ��ƣ���pos==0��ʾ��ǰΪ��ҵĻغϣ�����Ϊ�����Ļغ�
	flagfirst = true;	//�Ƿ��ǵ�һ����Ϸ
	direction = 1;
}

//��ʼ��ȱʧ��ɫ����
void Process::initLackColor() {
	vector<string> ii;
	ii.push_back("something");
	for (int i = 0; i < 4; i++) {
		lackColor.push_back(ii);
	}
}

bool Process::start() {
	Manager m;
	return m.managerMain();		//�Ƿ��¼�ɹ�
}

// ��Ϸ����������ҿ���ȱʧ����ɫ��¼ �������� char ��enum��ȷ��
void Process::recordPlayerColor() {
	string color = enumToString(receiveCard.color);
	vector<vector<string>>::iterator i = lackColor.begin();
	i += currentPos;
	if (flagPlusCard and !count(i->begin(), i->end(), color)) {	//��ǰ������� �Ҹ���ҵ�ȱʧ��ɫ��û�и���ɫ	
		i->push_back(color);
	}
	else if (!flagPlusCard and count(i->begin(), i->end(), color)) {
		for (vector<string>::iterator j = i->begin(); j != i->end(); j++) {
			if (*j == color) {
				j = i->erase(j);
				break;
			}
		}
	}
}


/*
//һ����Ϸ���� ����ҷ������� ���� չʾ �Ҹ�������ʾ��һ�����ƵĿ��Խ��вο�
void Process::computeScore() {
	vector<int> ScorePlayer;
	vector<Player>::iterator it = players.begin();
	for (it; it != players.end(); it++) {
		int sum = 0;
		while (it->head) {
			switch (it->head->data.number)
			{
			case 1:
				sum += 10;		//only a case 
				break;
			default:
				break;
			}
			it->head++;
		}
		ScorePlayer.push_back(sum);
	}
	//���score�������� ��ӡʤ������Ϣ���е����ˣ���д��
}
*/


//���� ÿ����Ϸ��������ҳ��� ����ҳ��� �Լ������Ƹ���
void Process::updateCard() {
	pPreCard = preCard;
	preCard = currentCard;
	receiveCard = preCard;
}

//���µ�ǰ���λ�� ������һ�����λ�� flag=1 ������һ����� 0 ���µ�ǰ��� 
void Process::updatePos(int &pos,int  flag) {
	if (direction == 1){
		pos++;	
	}
	else if (direction == -1) {
		pos--;
	}

	if (pos == -1) {
		pos = 3;
	}
	if (pos == 4) {
		pos = 0;
	}

	if (flag == 0) {
		cout << "��ǰ������ұ��" << pos << endl;
	}
	else {
		cout << "��һ����ұ��" << pos << endl;
	}
	
}

//���½����Ƶ���ɫ����Ҫ����ҳ���ɫ�ƺ����ɫ���� ���ַ�ת��
void Process::updateReceiveColor() {
	if (colorSelect == "red") {
		receiveCard.color = red;
	}
	else if (colorSelect == "yellow") {
		receiveCard.color = yellow;
	}
	else if (colorSelect == "green") {
		receiveCard.color = green;
	}
	else if (colorSelect == "blue") {
		receiveCard.color = blue;
	}
	cout << "�ϸ����ѡ����ɫ��" << colorSelect << endl;
}

//�����˺���ҵ�һ����Ϸ�Ľ�������˵���ƹ��� ������ תɫ��ɫ �Ƿ����Ƶ�ȷ��
void Process::roboAndPlayer(vector<Player>::iterator &it) {
	if (currentPos) {							//����ǰλ�÷�0����Ϊ������	
		unoMsg.RoboCompute();			//��ʾ��Ϣ
		//���� ��һ����� 
		int pos_next = currentPos;
		updatePos(pos_next,1);
		vector<Player>::iterator it_next = players.begin();
		it_next = it_next + pos_next;	//������λ�ü�1�������Ƿ����ֳ���������λ��
		int handSize = it_next->getHandCardSize(); 
		

		robo.RoboInit(preCard, handSize, pos_next, lackColor);	//��ʼ��
		//���robo�ĳ��� �����������Ϣ ����currentCard = ������ �������ƵĲ���ֵ
		//����currentCard flagIsGetCard  color ��ֵ

		vector<Card> playerCards;				//��ʼ����ز���
		playerCards = it->getPlayerCards();
		bool isQusePrePlayer = false;
		

		flagPlusCard = robo.roboOutMain(playerCards, isQusePrePlayer, flagPlusCard,currentCard); //�����ز���
		//cout << flagPlusCard << endl;
		if (flagPlusCard) {
			cout << "����������" << endl;
			it->handCardAdd(deck.getCard());		//��Ҽ��Ʋ��� �ƿ����
		}
		else {
			it->handCardRemove(robo.cardPosition(playerCards, currentCard));			//ע��˳���Ƿ��෴
			cout << "�����˳�λ��Ϊ��" << robo.cardPosition(playerCards, currentCard) << " ����"<< endl;
		}

		if (currentCard.number == 13 || currentCard.number == 14) { //��ɫ�Ƶ�ɫȷ��
			map<int, string> colorRobo;
			colorRobo = robo.getColorRobo(playerCards);
			colorSelect = robo.cardOutColor(currentCard,colorRobo);
			updateReceiveColor();
		}
		cout << "�����˳��ƣ�" << currentCard << endl;
		cout << "�����˳������" << endl;
	}
	else {
		cout << "��ǰ����������Ϣ���£�" << endl;
		it->printPlayer();			//��ӡ���������Ϣ

		int select;
		bool isLegal = false;			//�����Ƿ�Ϸ�
		while (!isLegal) {
			cout << "�ƿ�ʣ�ࣺ" << deck.getSize() << endl;
			unoMsg.CardsPlayMsg();		//������ʾ
			cin >> select;
			if (select == 1) {
				unoMsg.CardsOutMsg();
				cout << "�ο���Ϊ��" << currentCard << endl;
				int choice;			//���ƶѱ��
				//cout << "���������Ʊ�ţ�0-���ֵ" << endl;
				//����һ������choice �������Ҷ�Ӧ������
				cin >> choice;
				currentCard = it->handCardRemove(choice);	//�費��Ҫ-1��//ע��˳���Ƿ��෴
				isLegal = cardJudge(receiveCard, currentCard);
				if (!isLegal) {
					cout << "���Ʋ��Ϸ�" << endl;
					it->handCardAdd(currentCard);   //��Ϊ��ѭ���л�����ɾ���ÿ��ƣ����������Ϸ���Ӧ�ý��ÿ��ƷŻء�����ܣ�6.15
					it->printPlayer();
					//currentCard = receiveCard;
					//���˴�Ӧ�÷�װ����ѡ����Ƶ����ݣ�
				}
				else {
					cout << "�������Ϊ��" << currentCard << endl;;
				}

				if (currentCard.number == 13 || currentCard.number == 14) { //��ɫ��
					unoMsg.CardsColorChoice();
					string choice;		//��ɫѡ��  R Y B G
					cin >> choice;
					colorSelect = choice;
					updateReceiveColor(); 
				}
				flagPlusCard = false;					//�Ƿ����� false
			}
			else if (select == 2) {
				flagPlusCard = true;
				it->handCardAdd(deck.getCard());		//��Ҽ��Ʋ��� �ƿ����
				it->printPlayer();
				isLegal = true;
			}
			else if (select == 3 ) {
				cout << "��ѡ����Ʋ���" << endl;
				isLegal = true;
			}
			else {
				cout << "�������,����������" << endl;
				Sleep(1000);
				isLegal = false;
			}
		}
	}
}


//��һ����Ϸ�Ĺ���  ���Բο��Ǹ�excel ��������� ��������е��Σ����ܻ�д��
void Process::playStageFirst() {
	cout << "������Ϣ����" << "\t" <<receiveCard<<endl<<endl;
	
	if (receiveCard.number <= 9) {			//��ͨ������
		//updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//��õ�ǰ��ҵ�����
		roboAndPlayer(it);
		if (flagPlusCard) pPreCard = preCard;	//��ǰ�������
		else {
			updateCard();
		}
	}
	else if (receiveCard.number == 11) {	//����
		cout << "�ϼҴ�������ƣ����ֵ�ǰ��ҽ�ֹ����" << endl; 
		//updatePos(currentPos);
		pPreCard = preCard;
	}
	else if (receiveCard.number == 12) {	//ת��
		cout << "�ϸ����������Ϊת���ƣ�����ת��......." << endl;
		direction = -direction;
		updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//��õ�ǰ��ҵ�����
		cout << "ת�����" << endl;

		roboAndPlayer(it);
		if (flagPlusCard) pPreCard = preCard;	//��ǰ�������
		else {
			updateCard();
		}
	}
	else if (receiveCard.number == 10) {	//+2
		cout << "�ϼҴ��+2�ƣ���ǰ��ұ�����2��" << endl;
		//updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//��õ�ǰ��ҵ�����
		for (int i = 0; i < 2; i++) {
			it->handCardAdd(deck.getCard());
		}
		pPreCard = preCard;
	}
}

//�ǵ�һ�ֵ���Ϸ����
void Process::playStageNotFirst() {

	cout << "����һ��������Ϣ����" << "\t"<< pPreCard<<endl;
	cout << "��һ��������Ϣ����" << "\t" << preCard<<endl;
	cout << "���յ�������Ϣ����" << "\t" << receiveCard << endl; //�����ֺ�ɫתɫ�Ƶ�ʱ�������һ��������Ϣ��һ��
	if (flagPlusCard) cout << "��һ�����δ����" << endl<<endl;
	
	cout << "��������ʣ��:"<<endl ;
	int i = 0;
	for (vector<Player>::iterator itplay = players.begin(); itplay != players.end(); itplay++) {
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "��"<< i <<"�����ʣ���ƣ� " << itplay->getHandCardSize() << endl;
		itplay->printPlayer();
		i++;
		cout << endl;
	}
	cout << endl;

	if (receiveCard.number <= 9) {			//��ͨ������  <��Ϊ<= ����ܡ�6.15
		updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//��õ�ǰ��ҵ�����
		roboAndPlayer(it);
		updateCard();
	}
	else if (receiveCard.number == 11) {	//����
		updatePos(currentPos); 
		if (pPreCard.number == 11) {		//���ϼ�����
			vector<Player>::iterator it = players.begin();
			it += currentPos;		//��õ�ǰ��ҵ�����
			roboAndPlayer(it);
		}
		else {
			cout << "�ϼҴ�������ƣ����ֵ�ǰ��ֹ����" << endl;
		}
		updateCard();
	}
	else if (receiveCard.number == 12) {	//ת��
		
		vector<Player>::iterator it = players.begin();
		if (pPreCard.number != 12) {
			cout << "���ڽ���ת��......" << endl;
			direction = -direction;				//�ϸ������ת�� �Ƚ���ת�����
			cout << "ת�����" << endl;
		}
		updatePos(currentPos);
		it += currentPos;		//��õ�ǰ��ҵ�����
		roboAndPlayer(it);
		updateCard();
	}
	else if (receiveCard.number == 10) {	//+2
		updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//��õ�ǰ��ҵ�����
		if (pPreCard.number != 10) {
			cout << "�ϼҴ��+2�ƣ���ǰ��ұ�����2��" << endl;
			for (int i = 0; i < 2; i++) {
				it->handCardAdd(deck.getCard());
			}
		}
		else {
			roboAndPlayer(it);
		}
		updateCard();
	}
	else if (receiveCard.number == 13) {	//תɫ
		updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//��õ�ǰ��ҵ�����
		if (pPreCard.number != 13) {
			cout << "����תɫ" << endl;
			updateReceiveColor();	
		}
		roboAndPlayer(it);
		updateCard();
	}
	else if (receiveCard.number == 14) {	//תɫ +4
		updatePos(currentPos);
		vector<Player>::iterator it = players.begin();
		it += currentPos;		//��õ�ǰ��ҵ�����
		if (pPreCard.number != 14) {
			cout << "����תɫ....." << endl;
			cout << "תɫ���" << endl;
			cout << "������4��,���ֽ�ֹ����" << endl;
			updateReceiveColor();
			for (int i = 0; i < 4; i++) {
				it->handCardAdd(deck.getCard());
			}
		}
		else {
			roboAndPlayer(it);
			}
		updateCard();
	}
}

//��Ϸ������
bool Process::execute() {//return 0 ����Ϸ����
	
	while (true) {				//��ʼ��Ϸ���Ƿ��˳�
		if (!start()) return false; //����ʧ�ܷ���0���������
			
		if (!unoMenu.Menumain()) return false;  
		//�ɹ�������Ϸ
		
		// һ�ֿ�ʼ
		while (!flagEnd) {		//��ʼһ����Ϸ
			startUNO();			//��ʼ��Ϸ������һ����Ϸ�ĳ�ʼ��
			initLackColor();	//��ʼ��ȱʧ��ɫ����
			//һ�ֿ�ʼ
			while (!flagEnd) {
				//Context ct;//һ������ͼ�εļ򵥹�����ͨ��show���Ƶ�ǰ��Ϸ����
				//ct.show();
				
				if (flagfirst) {		//��һ�ֱ���
					
					playStageFirst();
				}
				else {					//�ǵ�һ�ֱ���
					playStageNotFirst();
				}

				
				flagfirst = false;
				recordPlayerColor();						//��¼��ǰ��ҵ�ȱʧ��ɫ

				vector<Player>::iterator it = players.begin();		//��õ�ǰ��ҵ�����
				it += currentPos;
				if (deck.getSize() == 0 || it->getHandCardSize() == 0)	//�ƿ����� ��ǰ�������Ϊ0
				{
					flagEnd = true;
				}
				system("pause");
				system("cls");
			}//һ�ֽ���
			//������� ���ʤ������Ϣ flagEnd �Ѿ�Ϊ�� ��Ϸ����
			//computeScore();
		}//һ�ֽ���
		//�Ƿ��˳���Ϸ ���˳�����������Ϸ��ʼ��һ�֣��˳���Ϸֱ���˳�
		//unoMenu.Menumain();
		cout << "������Ϸ����" << endl;
		system("pause");
		exit(0);
		break;
	}//��Ϸ����
}

//
//
////
//bool Process::Ques(Player& p) {
//	int flag = 0;
//	Context ct = Context(Draw("interface_Player_ADD_Query"));
//	ct.show();
//	string str;
//	cin >> str;
//	if (str == "Yes") flag = 1;
//	if (!flag) {
//		count = 4;
//		return 0;
//	}
//	if (find_if(p.begin(), p.end(), is_Num())) {
//		for (int i = 0; i < 4; ++i)
//			p.add_card(deck.Draw());
//		return 1;
//	}
//	else {
//		count = 6;
//		return 0;
//	}
//
//}
//
//