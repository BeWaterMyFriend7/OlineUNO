#include"robo.h"

bool judge(Card& card, Card& preCard)    //��6/11������
{
	if (card.number == 13 || card.number == 14)
		return true;
	if (card.color == preCard.color || card.number == preCard.number)
		return true;
	return false;
}

string enumToString2(int color) {
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

Robo::Robo() {

}

void Robo::RoboInit(Card preCard, int numnext, int nextplayer, vector<vector<string>> colorLack) {
	this->preCard = preCard;
	this->numNext = numnext;
	this->nextPlayer = nextplayer;
	this->colorLack = colorLack;
}

int Robo::cardPosition(vector<Card> &playerCards, Card &outCard){
	for (vector<Card>::iterator it = playerCards.begin(); it != playerCards.end(); it++)
	{
		if ((*it).color == outCard.color && (*it).number == outCard.number)
		{
			return it - playerCards.begin();
		} 
	}
}

vector<Card> Robo::getPlayerVaildCard(vector<Card> &playerCards)  //��6/11������
{
	vector<Card> vaildCards;
	for (auto playerCard : playerCards)
	{
		//�����ж��Ƿ���Ϲ����������������ƶ����������ƿ���ʹ��
		if (judge(playerCard, this->preCard))
		{
			vaildCards.push_back(playerCard);
		}
	}
	return vaildCards;
}

// 0612 �õ���ǰ����������Ƶ���ɫͳ�� 
map<int, string> Robo::getColorRobo(vector<Card> &playerCards) {
	map<int, string> colorRobo;
	//��������Ϊ������ɫ����
	int numR = 0;
	int numY = 0;
	int numB = 0;
	int numG = 0;
	for (vector<Card>::iterator it = playerCards.begin(); it != playerCards.end(); it++) {
		if (it->color == red) {
			numR++;
		}
		else if (it->color ==yellow) {
			numY++;
		}
		else if (it->color == blue) {
			numB++;
		}
		else {
			numG++;
		}
	}
	colorRobo.insert(pair<int, string>(numR, "red"));
	colorRobo.insert(pair<int, string>(numY, "yellow"));
	colorRobo.insert(pair<int, string>(numB, "blue"));
	colorRobo.insert(pair<int, string>(numG, "green"));//��ԭ�еġ�R��ת��ΪCardColor�ͣ������6.15

	return colorRobo;
}

//��һ�����������������3�ŵ�ʵ�� ���� �Ϸ����ƶѣ���� ��ǰ������������Ƶķ��� ����Խ��Խ���׳�������
vector<int> Robo::cardNumHigher3(vector<Card> &vaildCards) {
	vector<int> cardPoint;								//�����Ʒ�ֵvector���� ��һ����Ҷ���������ʱ ��ͨ����>��ֹ>��ת>��ɫ>+2>+4
	for (vector<Card>::iterator it = vaildCards.begin(); it != vaildCards.end(); it++) {
		if (it->number < 10 and it->number >0) {			//��ȥ0����ͨ������
			cardPoint.push_back(it->number + 10);
		}
		else if (it->number == 0) {				//0
			cardPoint.push_back(20);
		}
		else {									//��������
			switch (it->number) {
			case 11:							//����
				cardPoint.push_back(5);
				break;
			case 10:							//+2
				cardPoint.push_back(2);
				break;
			case 12:							//ת��
				cardPoint.push_back(4);
				break;
			case 13:							//תɫ
				cardPoint.push_back(3);
				break;
			case 14:							//+4
				cardPoint.push_back(1);
				break;
			}
		}
	}
	return cardPoint;
}

//�¼���������3���������ʱ���˻��������ȼ��㷨,������ϳ��ƹ�������ƶѣ���������ƶԶ�Ӧ��ֵ
vector<int> Robo::cardNumNotHigher3(vector<Card> &vaildCards)
{
	vector<int> cardPoint;										//����vector�����洢������Ʒ��ϳ��ƹ�����Ƶķ�ֵ����ֵԽ��Խ���ȳ�����
	for (auto card : vaildCards)
	{
		if (card.number < 10)//�ж�����������ƽ������в���
		{
			int flag = 0;					//0612 �����Ƿ�ӷֱ�־λ
			
			vector<vector<string>>::iterator it = this->colorLack.begin();			//ָ���һ�����û����ɫ��map�����ĵ�����
			
			it += this->nextPlayer;													//�õ���һ����ҵĵ�����
			for (vector<string>::iterator j = it->begin(); j != it->end(); j++) {		//������һ�����û����ɫ������
				if (*j == enumToString2(card.color)) {												//��ǰ������ɫ����һ�������û�е���ɫ
					flag = 1;				//�������Ѿ���ֵ
					if (card.number == 0)
					{
						cardPoint.push_back(10 + 9 );
					}
					else
					{
						cardPoint.push_back(card.number + 9);
					}
				}
			}
			
			if (flag == 0) {				//������δ��ֵ
				//��ǰ������ɫ������һ�������û�е���ɫ
				if (card.number == 0)//0�ƴ���10�֣�������ʾ
				{
					cardPoint.push_back(10);
				}
				else//ʣ��1-9�����ƼƷ�
				{
					cardPoint.push_back(card.number);
				}
			}
		}
		else if (card.number == 11)
		{
			//������˳�����ȼ�Ϊ4����ֵ22
			cardPoint.push_back(22);
		}
		else if (card.number == 10)
		{
			//��2��˳�����ȼ�Ϊ2����ֵ30
			cardPoint.push_back(30);
		}
		else if (card.number == 12)
		{
			//��ת��˳�����ȼ�Ϊ3����ֵ21
			cardPoint.push_back(21);
		}
		else if (card.number == 13)
		{
			//��ɫ��ɫ��˳�����ȼ�Ϊ5����ֵ20
			cardPoint.push_back(20);
		}
		else if (card.number == 14)
		{
			//��ɫ��4��˳�����ȼ�Ϊ1����ֵ40
			cardPoint.push_back(40);
		}
	}
	return cardPoint;
}


//���������ȷ�� ���뵱ǰ������Ʒ�ֵ�ͺϷ����ƶ� ���һ������ 
Card Robo::cardOut(vector<int> &cardPoint,vector<Card> &vaildCards) {
	vector<int> ::iterator indexMax = cardPoint.begin();								//��ʼ�����Ʒ�ֵ���ֵ
	for (vector<int>::iterator it = cardPoint.begin(); it != cardPoint.end(); it++) {	//Ѱ�����Ʒ�ֵ���ֵ
		if (*it > *indexMax) {
			indexMax = it;
		}
	}
	int inDex = indexMax - cardPoint.begin();					//��÷�ֵ��������ֵ

	Card cardOut = vaildCards.at(inDex);					//ȷ�������
	return cardOut;
}


//�����������ɫ ��������˳���ɫ�ƣ���ôתɫ��ȷ�� ������������ƣ���ô��ɫ��Ϊ��������ɫ ���뵱ǰ��������� ���char��ɫ
string Robo::cardOutColor(Card &card,map<int,string> &colorRobo) {
	string color;
	if (card.number == 13 or card.number == 14) {					//�����������ɫ��  //���ʣ�Ϊʲô���е�15���ƣ������.6.15
		//this->color_no
		if (this->numNext > 3) {								//��һ�������ʣ���ƴ���3
			map<int, string>::iterator it= colorRobo.begin();//map����ֵ�Զ���������keyֵ������ɫ�������������
			color = it->second;									//���������к�����ɫ������ɫ  //����������ɫ���ԣ����Խ������µ��޸ģ��˴���ʱ����Ϊblue
		}
		else {
			
			vector<vector<string>>::iterator it = this->colorLack.begin();			//ָ���һ�����û����ɫ��map�����ĵ�����
			it += this->nextPlayer;													//�õ���һ����ҵĵ�����

			for (vector<string>::iterator j = it->begin(); j != it->end(); j++) {		//������һ�����û����ɫ������
				map<int, string>::iterator i = colorRobo.end();					//ָ��ǰ������������ɫ�����һλ����ӵ������������ɫ����
				i--;
				for (i; i == colorRobo.begin(); i--) {						//��ǰѭ��
					if (*j == i->second) {					//��һ�����û�е�������ɫ�͵�ǰ��������ӵ�е�����ɫ�غ�
						color = *j;
						return color;
					}
				}
			}
			map<int, string>::iterator j = colorRobo.end();
			j--;
			color = j->second;			//��һ�����û�е�������ɫ�͵�ǰ��������ӵ�е�����ɫ���غϣ����������������ɫ����
		}
	}
	else {
		color = enumToString2(card.color);   //ö���������ַ�����ת��
	}
	return color;
}
/*
//�������Ƿ�������һ�����
bool Robo::isQusetion(Card &preCard) {
	vector<vector<char>>::iterator it = this->colorLack.begin();			//ָ���һ�����û����ɫ��map�����ĵ�����
	it += this->nextPlayer - 1;											//�õ���һ����ҵĵ���������ʱ��next_player��û�и��£�ָ��Ļ��ǵ�ǰ���
	for (vector<char>::iterator j = it->begin(); j != it->end(); j++) {		//������һ�����û����ɫ������
		if (*j == preCard.color) {											//�����һ�����ȷ��û�������ɫ
			return false;
		}
	}
	int y;																	//�����һ����Ҳ�ȷ���Ƿ��������ɫ������� 50%
	srand((unsigned)time(NULL));
	y = rand() % 10;
	if (y > 5) {
		return false;
	}
	else if (y < 5) {
		return true;
	}
}
*/



//��������ģ�� ��Ҫ��� �Ƿ����� �Ƿ����� ���� תɫ������Ҫ��ȷ����һ����Һ����
bool Robo::roboOutMain(vector<Card> &playerCards,bool &isQusePrePlayer,bool &isPickCard,Card &nowCard) {
	/*
	if (this->isQusetion(this->preCard))						//������һ�����
	{
		cout << "�������������" << endl;
		isQusePrePlayer = true;
	}
	else {
		isQusePrePlayer = false;
	}
	*/
	vector<Card> vaildCards = this->getPlayerVaildCard(playerCards);
	if (vaildCards.empty()) {					//�Ϸ���Ϊ��
		isPickCard = true;							//���ƣ���������Ϊ��ֵ
		return isPickCard;
	}
	else {										//�˻����ƹ���ʵ��
		isPickCard = false;
		vector<int> cardScore;
		if (this->numNext > 3) {
			cardScore = this->cardNumHigher3(vaildCards);	//�¸��������������3��ʱ�������ȼ�
		}
		else {
			cardScore = this->cardNumNotHigher3(vaildCards);		//�������ȼ�
		}

		nowCard = this->cardOut(cardScore,vaildCards);									//ȷ�����ƣ�����û��ȷ�������ɫ����Ҫ���������ִ�к�ȷ����һ����Һ����
		return isPickCard;
	}
	
}

/*
//��������ģ�飬��Ҫʵ�� �Ƿ����� �Ƿ����� �Ƿ���� תɫ���ܵ�ʵ�ֲ�������
bool Robo::roboOutMain(vector<Card> &vaildCards) {
	if (this->isQusetion(preCard))						//������һ�����
	{
		cout << "�������������" << endl;
	}

	if (vaild_cards.empty()) {					//�Ϸ���Ϊ��
		return true;							//���ƣ���������Ϊ��ֵ
	}
	else {										//�˻����ƹ���ʵ��
		vector<int> cardScore;
		if (this->numNext > 3) {
			cardScore = this->cardNumHigher3(this->validCards);	//�¸��������������3��ʱ�������ȼ�
		}
		else {
			cardScore = this->cardNumNotHigher3(this->validCards);		//�������ȼ�
		}
		
		this->cardOut(cardScore);									//ȷ�����ƣ�����û��ȷ�������ɫ����Ҫ���������ִ�к�ȷ����һ����Һ����
		
		return false;												//�����ƣ���������Ϊfalse
	}
}*/



Card Robo::computerReact(vector<Card> &playerCards)//��6/11�¼ӣ�
{
	vector<Card> v1 = this->getPlayerVaildCard(playerCards);
	vector<int> cardScore;
	if (this->numNext > 3) {
		cardScore = this->cardNumHigher3(v1);	//�¸��������������3��ʱ�������ȼ�
	}
	else {
		cardScore = this->cardNumNotHigher3(v1);		//�������ȼ�
	}
	return cardOut(cardScore,v1);
}
