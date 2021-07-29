
#include<string.h>
#include<string>
#include "card.h"
#include "player.h"
#include<iostream>


using namespace std;

Player::Player() {
	head = NULL;
	hand_size = 0;
}

Player::Player(const Player& other) {
	copy(other);
}

//��������
const Player& Player::operator=(const Player& other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}


Player::~Player() {
	clear();
}

//�����Ƶ���ǰ�����
void Player::handCardAdd(Card temp) {
	
	card_elem* temp_ptr;		//����һ����������
	temp_ptr = new card_elem;	//
	temp_ptr->data = temp;
	temp_ptr->next = head;
	head = temp_ptr;

	hand_size++;
}

//�����Ƴ�
Card Player::handCardRemove(int pos) {
	//λ�ó�����
	if (pos<0 || pos >=hand_size || !head) { //
		return Card();
	}
	//����ɾ������
	card_elem* prev_ptr = head;
	card_elem* target = prev_ptr->next;
	Card temp_card;
	int temp_pos = pos;

	//����λ��Ϊ��һ��
	if (pos == 0) {
		temp_card = head->data; //���淵�ص�����
		head = head->next;		//��ָ��ָ����һ��
		delete prev_ptr;		//ɾ��Ŀ��Ԫ��
		hand_size--;			
		return temp_card;
	}

	//�ҵ�ǰһԪ��
	while (temp_pos > 1) {
		prev_ptr = prev_ptr->next;
		target = prev_ptr->next;
		temp_pos--;
	} 
	prev_ptr->next = target->next; //������������Ԫ��
	temp_card = target->data;		//�����ݱ��浽tem
	delete target;					//ɾ��Ŀ��Ԫ��
	hand_size--;
	return temp_card;				//����Ŀ��Ԫ��
}

//��ӡ���
void Player::printPlayer() {
	int temp_size = hand_size;
	int i = 0;
	// card_elem* temp_ptr = head;
	while(temp_size > 0) {
		/*cout << "*"<<i << " " << temp_ptr->data << "  ";
		temp_ptr = temp_ptr->next;
		i++;
		if (i % 4 == 0) cout << endl;*/

		cout << "|   " << i << "   |  ";
		i++;
		temp_size--;
	}
	cout << endl;
	temp_size = hand_size;
	card_elem* temp_ptr = head;
	string color;
	while (temp_size > 0) {
		switch (temp_ptr->data.color)
		{
		case black: color = "black ";  break;
		case red: color =  "red   ";  break;
		case green: color = "green ";  break;
		case blue: color = "blue  ";  break;
		case yellow:color = "yellow";  break;
		default: color = "N/A   "; break;
		}
		
		cout << "| " << color << "|  ";
		temp_ptr = temp_ptr->next;
		temp_size--;
	}
	cout << endl;
	temp_size = hand_size;
	temp_ptr = head;
	string number;
	while (temp_size > 0) {
		switch (temp_ptr->data.number)
		{
		case 10: number = "+2     "; break;
		case 11: number = "SKIP   "; break;
		case 12: number = "REVERSE"; break;
		case 13: number = "WILD   "; break;
		case 14: number = "+4     "; break;
		default: number = to_string(temp_ptr->data.number) + "      "; break;
		}
		cout << "|" << number << "|  ";
		temp_ptr = temp_ptr->next;
		temp_size--;
	}
	cout << endl;
}
//��ȡ�����������
int Player::getHandCardSize() {
	return hand_size;
}



//��ҳ�ʼ��
void Player::initPlayer(Deck deck) {
	for (int i = 0; i < 7; i++) {
		this->handCardAdd(deck.getCard());
}
}

//���и��Ʋ���
void Player::copy(const Player& other) {
	hand_size = other.hand_size;

	//����Ŀ����ҵĶ���
	if (hand_size > 0) {
		head = new card_elem();
		head->data = other.head->data;
	}
	else {
		head = NULL;
		return;
	}
	//��other_ptr ����������
	card_elem* other_ptr = other.head->next;
	//����һ�������� temp_ptr ������������
	card_elem* temp_ptr;
	//����֮ǰ��ָ��ָ��ǰ
	card_elem* prev_ptr = head;
	for (int i = 1; i < hand_size; i++) {
		
		temp_ptr = new card_elem;			//������Ԫ��
		prev_ptr->next = temp_ptr;			//��һĿ��Ϊ����������
		temp_ptr->data = other_ptr->data;	//��ǰ���ݽ��뻺����
		prev_ptr = temp_ptr;				//��ǰ���ݷ�����һ����
		temp_ptr = NULL;					//��ǰ����Ϊ��
		other_ptr = other_ptr->next;		//ָ����һ����
	}
}
//��ղ���
void Player::clear() {
	card_elem* temp_ptr = head;
	card_elem* next_ptr;
	while (hand_size > 0) {
		next_ptr = temp_ptr->next;
		delete temp_ptr;
		temp_ptr = next_ptr;
		hand_size--;
	}
	head = NULL;
}

//��ȡ��ǰ��ҵ�������������ҪΪ�����˷���
vector<Card> Player::getPlayerCards()
{
	vector<Card> playerCards;
	card_elem* temp_head = head;
	while (head)
	{
		Card c;
		c.color = head->data.color;
		c.number = head->data.number;
		playerCards.push_back(c);
		head = head->next;
	}
	head = temp_head;
	//reverse(playerCards.begin(), playerCards.end());  //����player����ʽ�洢���õ���β�巨������Ҫ��ת
	return playerCards;
}







