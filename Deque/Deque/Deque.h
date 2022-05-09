#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include "Bag.h"

class Deck; // 전방 선언

template <class T>
class Deque : public Bag<T> //파생 클래스 Deque(Deque is-a-kind-of Bag)
{
	friend class Deck;
private:
	int front; // deque에서 첫 원소의 위치보다 하나 작은 위치
	int rear; // deque에서 마지막 원소의 위치

public:
	Deque(int dequeCapacity = 10);  // 생성자
	~Deque();						// 파괴자

	inline bool IsEmpty() const; 	//deque에 원소가 없는지 확인하는 함수

	void push_front(const T& x);	// front쪽으로 x값을 push하는 함수

	void push_rear(const T& x);		// rear쪽으로 x값을 push하는 함수

	T pop_front();				// 첫 원소를 deque에서 빼내고 그 값을 리턴하는 함수

	T pop_rear();				// 마지막 원소를 deque에서 빼내고 그 값을 리턴하는 함수

	void ChangeDequeSize(T*& a, const int oldSize, const int newSize);
	// deque의 크기를 부족한데 push하려는 경우에 호출되는 함수
	// deque의 크기를 newSize만큼 키워준다.
};

template <class T>
Deque<T>::Deque(int dequeCapacity): Bag<T>(dequeCapacity)
{ 
	front = rear = 0;
}
//Deque생성자는 Bag 생성자를 호출

template <class T>
Deque<T>::~Deque() { }
//Deque가 파괴될 때 Bag 파괴자는 자동으로 호출된다

template <class T>
inline bool Deque<T>::IsEmpty() const  { return front == rear; }

template <class T>
void Deque<T>::ChangeDequeSize(T*& a, const int oldSize, const int newSize)
{
	//만원이 된 Deque일 때 크기를 확장해주는 함수
	T* newDeque = new T[newSize];

	// Deque[front+1]과 Deque[capacity-1] 사이에 있는 원소들을 newDeque의 0에서부터 복사 넣기
	std::copy(a + front + 1, a + oldSize, newDeque);

	// Deque[0]와 Deque[rear]사이에 있는 원소들을 newDeque의 capacity- front - 1에서부터 복사 넣기
	if (!(front == 0)) // front가 0아닐 때만 실행
		std::copy(a, a + rear + 1, newDeque + oldSize - front - 1);

	delete[] a;
	a = newDeque;
	
	// rear, front, this->capacity 값 다시 지정
	rear = oldSize - 2;
	this->capacity = newSize;
	front = newSize - 1;
}

template <class T>
void Deque<T>::push_front(const T& x)
{
	if ((rear + 1) % this->capacity == front) { // 공간이 없는 경우로 큐의 크기 두배로 늘린다
		ChangeDequeSize(this->array, this->capacity, this->capacity * 2);
	}
	this->array[front] = x;
	// front값을 front가 0이면 (capacity-1), 아니면 (front - 1) 값으로 지정
	front = (front == 0) ? (this->capacity - 1) : (front - 1);
}

template <class T>
void Deque<T>::push_rear(const T& x)
{
	if ((rear + 1) % this->capacity == front) { // 공간이 없으므로 큐의 크기 두배로 늘린다
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
	this->array[front].~T(); // array[front]의 파괴자를 호출함으로 삭제
	return temp;
}

template <class T>
T Deque<T>::pop_rear()
{
	if (IsEmpty()) throw "Deque is empty. Cannot delete.";
	T temp = this->array[rear];
	this->array[rear].~T(); // array[rear]의 파괴자를 호출함으로 삭제
	// rear값을 rear가 0이면(capacity - 1), 아니면(rear - 1) 값으로 지정
	rear = (rear == 0) ? (this->capacity - 1) : (rear - 1);
	return temp;
}
#endif