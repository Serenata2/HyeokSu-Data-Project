#include <iostream>
#include <stdlib.h> // for srand function
#include <time.h> // for time function
#include "Deck.h"

#define NUM_CARDS 5 // ���� ���� ī���� ����

int main(void)
{
	int rank, suit;					 // ī���� ��ũ, ������ �����ϴ� ����
	bool in_hand[4][13] = { false }; // ���� ������ �ִ� ī������ �˷��ִ� �迭
	Deck* MyDeck = new Deck;

	srand((unsigned)time(NULL));	 // seed���� �����ϰ� ����

	int i = 1;
	while (i <= NUM_CARDS) {
		suit = rand() % 4;
		rank = rand() % 13;
		if (!in_hand[suit][rank]) {			   // �� �տ� ���� ī���� ����
			in_hand[suit][rank] = true;

			Card* temp = new Card(suit, rank); // ���õ� ������ ���߾ ���ο� Card��ü �����Ҵ�
			std::cout << "���� �� ī��" << i << " : ";
			temp->ShowCard();				   // ���õ� ī�� ��ü ���
			std::cout << std::endl;

			MyDeck->PushCard(*temp);		   // MyDeck�� ����Ʈ�� ���õ� ī�� ��ü push
			std::cout << std::endl;

			delete temp;					   // �޸� ����
			i++;
		}
	}
	delete MyDeck;
	return 0;
}