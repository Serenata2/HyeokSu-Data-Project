#ifndef DECK_H
#define DECK_H

#include <iostream>
#include "Chain.h"
#include "Card.h"

class Deck
{
private:
	Chain<Card> deck; // Card ��ü���� ���� ����Ʈ ���·� �����ϴ� deck ���� ����

public:
	void showDeck(); // Deck�� ��� �����͸� ����ϴ� �Լ�

	void PushCard(Card c); // Deck�� Card ��ü c�� push�ϰ� �����ϴ� ������ �����ִ� �Լ�
};

void Deck::showDeck()
{
	// �ݺ��ڸ� ���� ����Ʈ�� ��� ��忡 ����
	for (Chain<Card>::iterator ait = deck.begin(); ait != deck.end(); ++ait) {
		ait->ShowCard(); // �ݺ��ڰ� ����Ű�� ����� �������� ī�� ��ü ���
		std::cout << " ";
	}
	std::cout << std::endl;
}

void Deck::PushCard(Card c)
{
	this->showDeck();	 // ���� deck�� �ִ� ī��� ���
	deck.InsertFront(c); // Card ��ü c�� deck�� ����Ʈ �� �տ� push
	this->showDeck();	 // �ٽ� �ѹ� deck�� �ִ� ī��� ���

	//first, first->link�� ��� current�� ������ ������ �ݺ��� ait, bit����
	Chain<Card>::iterator ait = deck.begin(), bit = ++deck.begin();
	
	// �ݺ��� bit�� current�� 0�̰ų�
	// �ݺ����� current->data�� Card ��ü�� �켱�������� ait�� bit���� ���� ������ �ݺ�
	while (bit != deck.end() && *ait > *bit) {
		deck.NodeSwap(*ait); // ait�� current->data�� �μ��� �����Ѵ�.
		this->showDeck();
		++(++bit);			 // bit�� current�� current->link->link���� �ٲ۴�
	}
}


#endif
