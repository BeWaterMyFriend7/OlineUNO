#pragma once
#include "card.h"

class Deck {
public:
	friend class Player;
	friend class Robo;

	Deck();
	Deck(const Deck& other);
	const Deck& operator= (const Deck& other);
	~Deck();
	//���ƿ���г�ʼ��
	void Init();

	//ϴ��
	void Shuffle();

	//����һ�η��ƣ����ƣ�
	Card getCard();
	
	//���Ʋ���
	int addCard(Card temp_card);

	//��ӡ�ƿ�
	void printDeck();

	//��ȡ�ߴ�
	int getSize();


private:

	Card *ptr_deck;  //�����ƿ�
	int size;		//�Ƶĳߴ�
	void clear();	//���
	void copy(const Deck& other);	//����

};

