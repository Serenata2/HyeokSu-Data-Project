#ifndef CARD_H
#define CARD_H

#include <iostream>

class Deck; // ���漱��

class Card
{
	friend class Deck; // Card Ŭ������ Deck Ŭ������ ģ�� 
private:
	int suit; // ī���� ����
	int rank; // ī���� ��ũ
	char* suit_code[4]; // ī���� ������ ���� ��������� �����ϴ� �迭
public:
	// Card ��ü�� ���� �� �޾����� �μ����� ���� ī�带 �����.
	Card(int Suit = 0, int Rank = 0) :suit(Suit), rank(Rank), suit_code{ "��", "��", "��", "��" } { }
	~Card() { } // �ı���

	inline int Card_Order() { return (13 * suit + rank); } // ī���� �켱������ �˷��ִ� �Լ�
	
	void Show_Card() // ī�带 ����ϴ� �Լ�
	{
		std::cout << suit_code[suit] << rank + 1;
	}
};

#endif