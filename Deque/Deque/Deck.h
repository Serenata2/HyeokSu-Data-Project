#ifndef DECK_H
#define DECK_H

#include "Deque.h"
#include "Card.h"

class Deck
{
private:
	Deque<Card>*  deck; // Card ��ü�� �̷���� Deque ��ü�� �����ͺ���
	int card_num;	  // deck�� Card ��ü�� ������ �����ϴ� ����
public:
	Deck(int DequeCapacity = 6);	  // ������
	~Deck();					   	  // �ı���

	int Determind(Card& c);  
	// �� ���� Card ��ü c�� �ִ´ٸ� ��� �������� ��ŭ shift �ؾ��ϴ����� ���� ������ �˷��ִ� �Լ�
	// ���⼭ ������ ���� ���� ��ȣ�� ���� �����ǰ� shift�� ���� ���� ���񰪿� ���� �����ȴ�
	// ���� ���ϰ��� card_num�� ������ �� ���� shift�� 0���� ����Ѵ�

	void Push_Card(Card& c);
	// Card ��ü c�� �� ���� �־����� ������ ����ϴ� �Լ�

	void Show_Deck();
	// deck�� ī����� ������ ����ϴ� �Լ�
};
#endif