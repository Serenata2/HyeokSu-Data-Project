#ifndef CARD_H
#define CARD_H

#include <iostream>

class Deck; // 전방선언

class Card
{
	friend class Deck; // friend 선언
private:
	int suit; // 카드의 종류
	int rank; // 카드의 랭크

public:
	Card(int Suit = 0, int Rank = 0):suit(Suit), rank(Rank) { } // 생성자

	inline int Card_Order() const // 카드의 우선순위를 알려주는 함수
	{ 
		return (13 * suit + rank); 
	}

	inline void ShowCard() // 카드의 내용을 출력하는 함수
	{ 
		std::cout << suit_code[suit] << rank + 1; 
	}

	bool operator > (Card& c) const// 두 카드 객체의 우선순위를 비교해주는 연산자 오버로딩
	{ 
		return (this->Card_Order() > c.Card_Order()) ? true : false; 
	}

	bool operator != (Card& c) const // 두 카드 객체가 같은 값을 가지고 있는지 확인해주는 연산자 오버로딩
	{
		return (this->suit == c.suit && this->rank == c.rank) ? false : true;
	}

	static const char* suit_code[4]; // 카드의 종류에 따른 출력정보를 저장하는 배열
};
const char* Card::suit_code[4] = { "♠", "◆", "♥", "♣" };

#endif