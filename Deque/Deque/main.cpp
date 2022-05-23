#include <iostream>
#include <stdlib.h> // for srand function
#include <time.h> // for time function
#include "Deque.h"
#include "Deck.h"

#define NUM_CARDS 5 // 내가 가질 카드의 개수

int main(void)
{
	int rank, suit; // 카드의 랭크, 종류를 저장하는 변수
	bool in_hand[4][13] = { false }; // 내가 가지고 있는 카드인지 알려주는 배열
	Deck* My_Deck = new Deck; // 포인터 변수 My_Deck에 Deck객체를 동적할당
	
	srand((unsigned)time(NULL)); // seed값을 랜덤하게 설정

	int i = 1;
	while (i <= NUM_CARDS) { // NUM_CARDS개의 원하는 카드를 뽑을 때까지 반복
		suit = rand() % 4; // 랜덤하게 카드 선택
		rank = rand() % 13;
		if (!in_hand[suit][rank]) { // 내 손에 없는 카드라면 실행
			in_hand[suit][rank] = true;

			Card* temp = new Card(suit, rank); // 선택한 카드에 맞춰서 카드 객체 생성
			std::cout << "선택 된 카드" << i << " : ";
			temp->Show_Card(); // 선택한 카드 객체 출력
			std::cout << std::endl; 

			My_Deck->Push_Card(*temp); // 선택한 카드를 내 덱에 넣기 위한 과정들 출력
			std::cout << std::endl;

			delete temp; // temp에 할당된 메모리 해제
			i++;
		}
	}

	delete My_Deck; // My_Deck에 할당된 메모리 해제

	return 0;
}