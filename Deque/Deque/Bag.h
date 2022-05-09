#ifndef BAG_H
#define BAG_H

#include <iostream>

template <class T>
class Bag // �⺻ Ŭ���� Bag
{
protected:
	T* array;
	int capacity; // �迭�� ũ��
	int top; // �迭���� ���Ұ� ��� �ִ� ���� ���� ��ġ

public:
	Bag(int stackCapacity = 10) :capacity(stackCapacity)
	{
		if (capacity < 1) throw "Capacity must be > 0";
		array = new T[capacity]; // �μ������� ���� capacity��ŭ�� ������ T �迭 �����Ҵ�
		top = -1;
	}

	virtual ~Bag() // �ı���
	{
		delete[] array;
	}

	virtual inline bool IsEmpty() const // ���� ��������̸� True, �ƴϸ� False
	{
		return (top+1) == 0;
	}

	virtual inline T& Element() const // �鿡 �ִ� TŸ�� ���Ҹ� ��ȯ
	{
		if (IsEmpty()) throw "empty!!";
		return array[0];
	}

	virtual void push(const T& x)// TŸ���� ���� �ϳ��� �鿡 ���� 
	{
		if (capacity == (top + 1)) {
			ChangeSize1D(array, capacity, 2 * capacity);
			capacity *= 2;
		}
		array[++top] = x;
	}

	virtual void pop() // �鿡�� ���Ҹ� ����
	{
		if (IsEmpty()) throw "Bag is empty, cannot delete";
		int deletePos = top / 2;
		std::copy(array + deletePos + 1, array + top + 1, array + deletePos); // �迭 ����
		array[top--].~T();
	}

	void ChangeSize1D(T*& a, const int oldSize, const int newSize)
	{
		if (newSize < 0)
			throw "New length must be >= 0";

		T* temp = new T[newSize];            // ���ο� �迭
		int number = std::min(oldSize, newSize);  // ������ ���� ��
		std::copy(a, a + number, temp);
		delete[]a;                          // ���� �޸� ����
		a = temp;
	}
};
#endif