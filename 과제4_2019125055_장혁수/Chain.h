#ifndef CHAIN_H
#define CHAIN_H

#include <iostream>

template <class T> class Chain; // ���� ����

template <class T>
class ChainNode 
{
	template <class T> friend class Chain; // friend ����
private:
	T data;			 // TŸ���� �����͸� �����ϴ� ����
	ChainNode* link; // ���Ḯ��Ʈ�� ���� ��带 ����Ű�� ������

public:
	ChainNode(T d, ChainNode* next = 0):data(d), link(next){ } // ������
};


template <class T>
class Chain
{
private:
	ChainNode<T>* first; // ����Ʈ�� ù��° ��带 ����Ű�� ������
public:
	Chain();		  	 // ������

	~Chain() { this->freeAll(); }  // freeAll�Լ��� ȣ���ϴ� �ı���

	void freeAll();		 //����� ��� ChainNode�� �޸𸮸� �����ϴ� �Լ�

	void InsertFront(const T& e);  // ������ e�� ���� ��� �����ϰ� ����Ʈ�� �Ǿտ� push�Ѵ�.

	void NodeSwap(T& e); // ������e�� ������ �ִ� ���� �� ������ ��带 swap�ϴ� �Լ�

	class iterator {	 // �ݺ���
	private:
		ChainNode<T>* current;	   // �ݺ��ڰ� ��Ÿ���� ����� �ּҰ��� ������ ����

	public:
		iterator(ChainNode<T> * startNode = 0) : current(startNode){ } // ������

		//������ ������
		T& operator* () const { return current->data; } 
		T* operator->() const { return &current->data; }

		iterator& operator++() { // ��������
			current = current->link;
			return *this;
		}
		iterator operator++(int) { // ��������
			iterator old = *this;
			current = current->link;
			return old;
		}

		//���� �˻�
		bool operator != (const iterator right) const {
			return current != right.current;
		}
		bool operator == (const iterator right) const {
			return current == right.current;
		}
	}; // end of iterator

	iterator begin() // first�� current�� ������ �ݺ��� ��ȯ
	{ 
		return iterator(first);
	}
	iterator end() // NULL�� current�� ������ �ݺ��� ��ȯ
	{
		return iterator(NULL);
	}
};

template <class T>
Chain<T>::Chain() { first = NULL; } // �����ڷ� first = 0���� �ʱ�ȭ

template <class T>
void Chain<T>::freeAll()
{
	// ����� link�� ���󰡸鼭 ��� ����� �޸� ����
	while (first != NULL) { 
		ChainNode<T>* temp = first;
		first = first->link;
		delete temp;
	}
}

template <class T>
void Chain<T>::InsertFront(const T& e)
{
	// e �����͸� ������ ���ο� ��� �Ҵ��԰� ���ÿ� ����Ʈ �� �տ� push
	first = new ChainNode<T>(e,first);
}

template <class T>
void Chain<T>::NodeSwap(T& e)
{
	ChainNode<T>* current = first, *previous = NULL;// previous�� current�� ���󰣴�.

	while (e != current->data && current != NULL) { // current�� �����Ͱ� �μ��� ���� ������ e�� ���ų�
		previous = current;							// Ȥ�� ���� ����Ʈ ������ �� ������ �ݺ�
		current = current->link;
	}

	if (current == NULL) {							// ã�� �ִ� ��尡 ���� ���
		std::cout << "���ϴ� ��尡 ����Ʈ�� �����ϴ�" << std::endl;
		return;
	}

	ChainNode<T>* nextNode = current->link;			// current->link�� ������ ���ο� ��� ������ ����

	if (current == first) {							// current�� first�� ���
		current->link = nextNode->link;
		nextNode->link = current;
		first = nextNode;
 	}

	else if(nextNode != NULL) {						// current�� ������ ��尡 �ƴ� ���
		previous->link = nextNode;
		current->link = nextNode->link;
		nextNode->link = current;
	}
} 
#endif
