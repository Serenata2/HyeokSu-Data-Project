#ifndef DECK_H
#define DECK_H

#include <iostream>
#include "Chain.h"
#include "Card.h"

class Deck
{
private:
	Chain<Card> deck; // Card 객체들을 연결 리스트 형태로 저장하는 deck 변수 선언

public:
	void showDeck(); // Deck의 모든 데이터를 출력하는 함수

	void PushCard(Card c); // Deck에 Card 객체 c를 push하고 정렬하는 과정을 보여주는 함수
};

void Deck::showDeck()
{
	// 반복자를 통해 리스트의 모든 노드에 접근
	for (Chain<Card>::iterator ait = deck.begin(); ait != deck.end(); ++ait) {
		ait->ShowCard(); // 반복자가 가리키는 노드의 데이터인 카드 객체 출력
		std::cout << " ";
	}
	std::cout << std::endl;
}

void Deck::PushCard(Card c)
{
	this->showDeck();	 // 먼저 deck에 있는 카드들 출력
	deck.InsertFront(c); // Card 객체 c를 deck의 리스트 맨 앞에 push
	this->showDeck();	 // 다시 한번 deck에 있는 카드들 출력

	//first, first->link을 멤버 current의 값으로 가지는 반복자 ait, bit선언
	Chain<Card>::iterator ait = deck.begin(), bit = ++deck.begin();
	
	// 반복자 bit의 current가 0이거나
	// 반복자의 current->data인 Card 객체의 우선순위에서 ait이 bit보다 낮을 때까지 반복
	while (bit != deck.end() && *ait > *bit) {
		deck.NodeSwap(*ait); // ait의 current->data를 인수로 전달한다.
		this->showDeck();
		++(++bit);			 // bit의 current를 current->link->link으로 바꾼다
	}
}


#endif
