#include <iostream>
#include <stdlib.h> // for srand function
#include <time.h> // for time function
#include "Deck.h"

#define NUM_CARDS 5 // 내가 가질 카드의 개수

int main(void)
{
	int rank, suit;					 // 카드의 랭크, 종류를 저장하는 변수
	bool in_hand[4][13] = { false }; // 내가 가지고 있는 카드인지 알려주는 배열
	Deck* MyDeck = new Deck;

	srand((unsigned)time(NULL));	 // seed값을 랜덤하게 설정

	int i = 1;
	while (i <= NUM_CARDS) {
		suit = rand() % 4;
		rank = rand() % 13;
		if (!in_hand[suit][rank]) {			   // 내 손에 없는 카드라면 실행
			in_hand[suit][rank] = true;

			Card* temp = new Card(suit, rank); // 선택된 정보에 맞추어서 새로운 Card객체 동적할당
			std::cout << "선택 된 카드" << i << " : ";
			temp->ShowCard();				   // 선택된 카드 객체 출력
			std::cout << std::endl;

			MyDeck->PushCard(*temp);		   // MyDeck의 리스트에 선택된 카드 객체 push
			std::cout << std::endl;

			delete temp;					   // 메모리 해제
			i++;
		}
	}
	delete MyDeck;
	return 0;
}