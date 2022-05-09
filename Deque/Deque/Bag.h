#ifndef BAG_H
#define BAG_H

#include <iostream>

template <class T>
class Bag // 기본 클래스 Bag
{
protected:
	T* array;
	int capacity; // 배열의 크기
	int top; // 배열에서 원소가 들어 있는 가장 높은 위치

public:
	Bag(int stackCapacity = 10) :capacity(stackCapacity)
	{
		if (capacity < 1) throw "Capacity must be > 0";
		array = new T[capacity]; // 인수값으로 받은 capacity만큼의 길이의 T 배열 동적할당
		top = -1;
	}

	virtual ~Bag() // 파괴자
	{
		delete[] array;
	}

	virtual inline bool IsEmpty() const // 백이 공백상태이면 True, 아니면 False
	{
		return (top+1) == 0;
	}

	virtual inline T& Element() const // 백에 있는 T타입 원소를 반환
	{
		if (IsEmpty()) throw "empty!!";
		return array[0];
	}

	virtual void push(const T& x)// T타입의 원소 하나를 백에 삽입 
	{
		if (capacity == (top + 1)) {
			ChangeSize1D(array, capacity, 2 * capacity);
			capacity *= 2;
		}
		array[++top] = x;
	}

	virtual void pop() // 백에서 원소를 제거
	{
		if (IsEmpty()) throw "Bag is empty, cannot delete";
		int deletePos = top / 2;
		std::copy(array + deletePos + 1, array + top + 1, array + deletePos); // 배열 정리
		array[top--].~T();
	}

	void ChangeSize1D(T*& a, const int oldSize, const int newSize)
	{
		if (newSize < 0)
			throw "New length must be >= 0";

		T* temp = new T[newSize];            // 새로운 배열
		int number = std::min(oldSize, newSize);  // 복사할 원소 수
		std::copy(a, a + number, temp);
		delete[]a;                          // 이전 메모리 제거
		a = temp;
	}
};
#endif