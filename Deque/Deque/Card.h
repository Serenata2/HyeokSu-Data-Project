#ifndef CARD_H
#define CARD_H

#include <iostream>

class Deck; // 전방선언

class Card
{
	friend class Deck; // Card 클래스는 Deck 클래스의 친구 
private:
	int suit; // 카드의 종류
	int rank; // 카드의 랭크
	char* suit_code[4]; // 카드의 종류에 따른 출력정보를 저장하는 배열
public:
	// Card 객체를 만들 때 받아지는 인수값에 따라 카드를 만든다.
	Card(int Suit = 0, int Rank = 0) :suit(Suit), rank(Rank), suit_code{ "♠", "◆", "♥", "♣" } { }
	~Card() { } // 파괴자

	inline int Card_Order() { return (13 * suit + rank); } // 카드의 우선순위를 알려주는 함수
	
	void Show_Card() // 카드를 출력하는 함수
	{
		std::cout << suit_code[suit] << rank + 1;
	}
};

#endif