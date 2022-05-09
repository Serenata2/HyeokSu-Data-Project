#ifndef DECK_H
#define DECK_H

#include "Deque.h"
#include "Card.h"

class Deck
{
private:
	Deque<Card>*  deck; // Card 객체로 이루어진 Deque 객체의 포인터변수
	int card_num;	  // deck에 Card 객체의 개수를 저장하는 변수
public:
	Deck(int DequeCapacity = 6);	  // 생성자
	~Deck();					   	  // 파괴자

	int Determind(Card& c);  
	// 내 덱에 Card 객체 c를 넣는다면 어느 방향으로 얼만큼 shift 해야하는지에 대한 정보를 알려주는 함수
	// 여기서 방향은 리턴 값의 부호에 따라 결정되고 shift은 리턴 값의 절댓값에 따라 결정된다
	// 만약 리턴값이 card_num과 같으면 그 경우는 shift는 0으로 계산한다

	void Push_Card(Card& c);
	// Card 객체 c가 내 덱에 넣어지는 과정을 출력하는 함수

	void Show_Deck();
	// deck의 카드들의 정보를 출력하는 함수
};
#endif