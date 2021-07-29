#pragma once
#define CARD
#include <iostream>
#include<vector>

using namespace std;

enum  CardColor{ red, green, blue, yellow, black };
/*
const char* CardColorname[] = { "red", "green", "blue", "yellow", "black" };
string getCardColor(CardColor type)
{
	int idx = static_cast<int>(type);
	return CardColorname[idx];
}
*/

class Card
{
public:
	int number; // 0-9 numbers, 10->+2, 11->skip, 12->reverse, 13->all color, 14->+4 (all color) 
	CardColor color; // ������ɫ���졢�ơ������̡���

	//���ͼ�飺��ͬ
	bool operator==(Card const& other) const;


	//���ͼ�飺����ͬ
	bool operator!=(Card const& other) const;

	Card();


	Card(int num, CardColor color);

	//~Card();
};

ostream& operator<<(ostream& out, Card const& temp_card);

