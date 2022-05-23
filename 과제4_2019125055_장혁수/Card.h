#ifndef CARD_H
#define CARD_H

#include <iostream>

class Deck; // ���漱��

class Card
{
	friend class Deck; // friend ����
private:
	int suit; // ī���� ����
	int rank; // ī���� ��ũ

public:
	Card(int Suit = 0, int Rank = 0):suit(Suit), rank(Rank) { } // ������

	inline int Card_Order() const // ī���� �켱������ �˷��ִ� �Լ�
	{ 
		return (13 * suit + rank); 
	}

	inline void ShowCard() // ī���� ������ ����ϴ� �Լ�
	{ 
		std::cout << suit_code[suit] << rank + 1; 
	}

	bool operator > (Card& c) const// �� ī�� ��ü�� �켱������ �����ִ� ������ �����ε�
	{ 
		return (this->Card_Order() > c.Card_Order()) ? true : false; 
	}

	bool operator != (Card& c) const // �� ī�� ��ü�� ���� ���� ������ �ִ��� Ȯ�����ִ� ������ �����ε�
	{
		return (this->suit == c.suit && this->rank == c.rank) ? false : true;
	}

	static const char* suit_code[4]; // ī���� ������ ���� ��������� �����ϴ� �迭
};
const char* Card::suit_code[4] = { "��", "��", "��", "��" };

#endif