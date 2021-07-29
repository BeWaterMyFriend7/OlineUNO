
#include<string.h>
#include "card.h"
#include"deck.h"


class Player {	
public:
	friend class Process;

	string name;		//�������
	//�������
	Player();
	Player(const Player& other);
	//�߼�����
	const Player & operator=(const Player& other);
	//�������
	friend ostream& operator <<(ostream& os, const Player& player);

	~Player();

	//������м���
	void handCardAdd(Card temp);
	//������м���
	Card handCardRemove(int pos);
	//��ӡ���
	void printPlayer();
	//��ȡ�����������
	int getHandCardSize();
	//��ҳ�ʼ��
	void initPlayer(Deck deck);

	vector<Card> getPlayerCards(); //��ȡ��ǰ��ҵ�������������ҪΪ�����˷���
	

private:
	const std::string mUsername;
	//�����ࣺ����Ԫ��
	class card_elem {
	public:
		card_elem() {
			next = NULL;
		}
		card_elem* next;
		Card data;
	};
	int hand_size;
	card_elem* head;
	void copy(const Player& other);
	void clear();
	
};

