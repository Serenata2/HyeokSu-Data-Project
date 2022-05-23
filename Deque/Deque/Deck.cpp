#include <iostream>
#include "Deck.h"


Deck::Deck(int DequeCapacity)// ������
{
	deck = new Deque<Card>(DequeCapacity); // �μ��� �޴� ����ŭ Deque<Card> �����Ҵ�
	card_num = 0; // 0���� �ʱ�ȭ
}

Deck::~Deck() { delete deck; } // �ı���

int Deck::Determind(Card& c)
{
	int k = 0; // c�� �� ��° �켱������ ������ �����ϴ� ����

	// this�� deck�� �ִ� ��� Card ��ü�� ����
	for (int i = deck->front; i != deck->rear; i = (i + 1) % deck->capacity, k++) { 
		int j = (i + 1) % deck->capacity;
		if (c > deck->array[j]) // c�� order�� Deck�� array[j]�� order���� ū ���
			continue;

		if (k > (int)(card_num / 2))   // right shift �ϸ� ���� ��
			return card_num - k;
		else						   // left shift �ϸ� ���� ��
			return -k;
	}

	// ������ ��� k ����(1. Deck�� �ƹ��͵� ���� ���, 2. order�� ���� ū ���)
	// ���� 0, card_num �� �����Ѵ�
	return k;
}

void Deck::Push_Card(Card& c)
{
	int Shift_Num = Determind(c); // ��� �������� �󸶸�ŭ shift�ؾ��ϴ����� ������ 
	Show_Deck(); // ���� ���� ���� ���¸� ������

	if (Shift_Num > 0) { // Shift_Num�� 0���� ū ���, ó���� right_shift�ϱ�
		if (Shift_Num == card_num) Shift_Num = 0;
		// Shift_Num�� card_num�� ������ Shift_Num�� 0���� �ٲٱ�

		for (int i = 0; i < Shift_Num; i++) { // right_shift�� Shift_Num��ŭ �ݺ�
			deck->push_front(deck->pop_rear());
			Show_Deck();
		}
		deck->push_rear(c); // rear������ Card��ü c push
		Show_Deck();
		for (int i = 0; i < Shift_Num; i++) { // left_shift�� Shift_Num��ŭ �ݺ�
			deck->push_rear(deck->pop_front());
			Show_Deck();
		}
	}

	else {				// Shift_Num�� 0������ ���, ó���� left_shift�ϱ�
		Shift_Num *= -1;
		// Shift_Num�� -1�� ���ؼ� ����� �ǰ� �ϱ�

		for (int i = 0; i < Shift_Num; i++) { // left_shift�� Shift_Num��ŭ �ݺ�
			deck->push_rear(deck->pop_front());
			Show_Deck();
		}
		deck->push_front(c);				  //front������ Card��ü c push
		Show_Deck();
		for (int i = 0; i < Shift_Num; i++) { // right_shift�� Shift_Num��ŭ �ݺ�
			deck->push_front(deck->pop_rear());
			Show_Deck();
		}
	}
	card_num++; 
}

void Deck::Show_Deck()
{
	// this�� deck�� �ִ� ��� Card ��ü�� ����
	for (int i = deck->front; i != deck->rear; i = (i + 1) % deck->capacity) {
		int j = (i + 1) % deck->capacity;
		deck->array[j].Show_Card();
		std::cout << " ";
	}
	std::cout << std::endl;
}