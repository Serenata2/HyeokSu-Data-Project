#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include "Bag.h"

class Deck; // ���� ����

template <class T>
class Deque : public Bag<T> //�Ļ� Ŭ���� Deque(Deque is-a-kind-of Bag)
{
	friend class Deck;
private:
	int front; // deque���� ù ������ ��ġ���� �ϳ� ���� ��ġ
	int rear; // deque���� ������ ������ ��ġ

public:
	Deque(int dequeCapacity = 10);  // ������
	~Deque();						// �ı���

	inline bool IsEmpty() const; 	//deque�� ���Ұ� ������ Ȯ���ϴ� �Լ�

	void push_front(const T& x);	// front������ x���� push�ϴ� �Լ�

	void push_rear(const T& x);		// rear������ x���� push�ϴ� �Լ�

	T pop_front();				// ù ���Ҹ� deque���� ������ �� ���� �����ϴ� �Լ�

	T pop_rear();				// ������ ���Ҹ� deque���� ������ �� ���� �����ϴ� �Լ�

	void ChangeDequeSize(T*& a, const int oldSize, const int newSize);
	// deque�� ũ�⸦ �����ѵ� push�Ϸ��� ��쿡 ȣ��Ǵ� �Լ�
	// deque�� ũ�⸦ newSize��ŭ Ű���ش�.
};

template <class T>
Deque<T>::Deque(int dequeCapacity): Bag<T>(dequeCapacity)
{ 
	front = rear = 0;
}
//Deque�����ڴ� Bag �����ڸ� ȣ��

template <class T>
Deque<T>::~Deque() { }
//Deque�� �ı��� �� Bag �ı��ڴ� �ڵ����� ȣ��ȴ�

template <class T>
inline bool Deque<T>::IsEmpty() const  { return front == rear; }

template <class T>
void Deque<T>::ChangeDequeSize(T*& a, const int oldSize, const int newSize)
{
	//������ �� Deque�� �� ũ�⸦ Ȯ�����ִ� �Լ�
	T* newDeque = new T[newSize];

	// Deque[front+1]�� Deque[capacity-1] ���̿� �ִ� ���ҵ��� newDeque�� 0�������� ���� �ֱ�
	std::copy(a + front + 1, a + oldSize, newDeque);

	// Deque[0]�� Deque[rear]���̿� �ִ� ���ҵ��� newDeque�� capacity- front - 1�������� ���� �ֱ�
	if (!(front == 0)) // front�� 0�ƴ� ���� ����
		std::copy(a, a + rear + 1, newDeque + oldSize - front - 1);

	delete[] a;
	a = newDeque;
	
	// rear, front, this->capacity �� �ٽ� ����
	rear = oldSize - 2;
	this->capacity = newSize;
	front = newSize - 1;
}

template <class T>
void Deque<T>::push_front(const T& x)
{
	if ((rear + 1) % this->capacity == front) { // ������ ���� ���� ť�� ũ�� �ι�� �ø���
		ChangeDequeSize(this->array, this->capacity, this->capacity * 2);
	}
	this->array[front] = x;
	// front���� front�� 0�̸� (capacity-1), �ƴϸ� (front - 1) ������ ����
	front = (front == 0) ? (this->capacity - 1) : (front - 1);
}

template <class T>
void Deque<T>::push_rear(const T& x)
{
	if ((rear + 1) % this->capacity == front) { // ������ �����Ƿ� ť�� ũ�� �ι�� �ø���
		ChangeDequeSize(array, this->capacity, this->capacity * 2);
	}
	rear = (rear + 1) % this->capacity;
	this->array[rear] = x;
}

template <class T>
T Deque<T>::pop_front()
{
	if (IsEmpty()) throw "Deque is empty. Cannot delete.";
	front = (front + 1) % this->capacity;
	T temp = this->array[front];
	this->array[front].~T(); // array[front]�� �ı��ڸ� ȣ�������� ����
	return temp;
}

template <class T>
T Deque<T>::pop_rear()
{
	if (IsEmpty()) throw "Deque is empty. Cannot delete.";
	T temp = this->array[rear];
	this->array[rear].~T(); // array[rear]�� �ı��ڸ� ȣ�������� ����
	// rear���� rear�� 0�̸�(capacity - 1), �ƴϸ�(rear - 1) ������ ����
	rear = (rear == 0) ? (this->capacity - 1) : (rear - 1);
	return temp;
}
#endif