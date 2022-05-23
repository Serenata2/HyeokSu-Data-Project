#include <iostream>
#include <stdlib.h> // for srand function
#include <time.h> // for time function
#include "Deque.h"
#include "Deck.h"

#define NUM_CARDS 5 // ���� ���� ī���� ����

int main(void)
{
	int rank, suit; // ī���� ��ũ, ������ �����ϴ� ����
	bool in_hand[4][13] = { false }; // ���� ������ �ִ� ī������ �˷��ִ� �迭
	Deck* My_Deck = new Deck; // ������ ���� My_Deck�� Deck��ü�� �����Ҵ�
	
	srand((unsigned)time(NULL)); // seed���� �����ϰ� ����

	int i = 1;
	while (i <= NUM_CARDS) { // NUM_CARDS���� ���ϴ� ī�带 ���� ������ �ݺ�
		suit = rand() % 4; // �����ϰ� ī�� ����
		rank = rand() % 13;
		if (!in_hand[suit][rank]) { // �� �տ� ���� ī���� ����
			in_hand[suit][rank] = true;

			Card* temp = new Card(suit, rank); // ������ ī�忡 ���缭 ī�� ��ü ����
			std::cout << "���� �� ī��" << i << " : ";
			temp->Show_Card(); // ������ ī�� ��ü ���
			std::cout << std::endl; 

			My_Deck->Push_Card(*temp); // ������ ī�带 �� ���� �ֱ� ���� ������ ���
			std::cout << std::endl;

			delete temp; // temp�� �Ҵ�� �޸� ����
			i++;
		}
	}

	delete My_Deck; // My_Deck�� �Ҵ�� �޸� ����

	return 0;
}