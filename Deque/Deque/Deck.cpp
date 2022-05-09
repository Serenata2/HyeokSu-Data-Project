#include <iostream>
#include "Deck.h"


Deck::Deck(int DequeCapacity)// 생성자
{
	deck = new Deque<Card>(DequeCapacity);
	card_num = 0; // 0으로 초기화
}

Deck::~Deck() { delete deck; } // 파괴자

int Deck::Determind(Card& c)
{
	int order = c.Card_Order(); // Card객체 c의 우선순위를 저장하는 변수
	int k = 0; // c가 몇 번째 우선순위를 갖는지 저장하는 변수

	// this의 deck에 있는 모든 Card 객체에 접근
	for (int i = deck->front; i != deck->rear; i = (i + 1) % deck->capacity, k++) { 
		int j = (i + 1) % deck->capacity;
		if (order > deck->array[j].Card_Order()) // order가 Deck의 array[j]의 order보다 큰 경우
			continue;

		if (k > (int)(card_num / 2)) // right shift 하면 좋을 때
			return card_num - k;
		else						   // left shift 하면 좋을 때
			return -k;
	}

	// 나머지 경우 k 리턴(1. Deck에 아무것도 없는 경우, 2. order가 가장 큰 경우)
	// 각각 0, card_num 값 리턴한다
	return k;
}

void Deck::Push_Card(Card& c)
{
	int Shift_Num = Determind(c);
	Show_Deck(); // 먼저 현재 덱의 상태를 보여줌

	if (Shift_Num > 0) { // Shift_Num이 0보다 큰 경우
		if (Shift_Num == card_num) Shift_Num = 0;
		// Shift_Num이 card_num과 같으면 Shift_Num은 0으로 바꾸기

		for (int i = 0; i < Shift_Num; i++) { // right_shift를 Shift_Num만큼 반복
			deck->push_front(deck->pop_rear());
			Show_Deck();
		}
		deck->push_rear(c); // rear쪽으로 Card객체 c push
		Show_Deck();
		for (int i = 0; i < Shift_Num; i++) { // left_shift를 Shift_Num만큼 반복
			deck->push_rear(deck->pop_front());
			Show_Deck();
		}
	}

	else {				// Shift_Num이 0이하인 경우
		Shift_Num *= -1;
		// Shift_Num에 -1을 곱해서 절댓값 구하기

		for (int i = 0; i < Shift_Num; i++) { // left_shift를 Shift_Num만큼 반복
			deck->push_rear(deck->pop_front());
			Show_Deck();
		}
		deck->push_front(c);
		Show_Deck();
		for (int i = 0; i < Shift_Num; i++) { // right_shift를 Shift_Num만큼 반복
			deck->push_front(deck->pop_rear());
			Show_Deck();
		}
	}
	card_num++; 
}

void Deck::Show_Deck()
{
	// this의 deck에 있는 모든 Card 객체에 접근
	for (int i = deck->front; i != deck->rear; i = (i + 1) % deck->capacity) {
		int j = (i + 1) % deck->capacity;
		deck->array[j].Show_Card();
		std::cout << " ";
	}
	std::cout << std::endl;
}