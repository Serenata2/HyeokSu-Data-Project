#ifndef CHAIN_H
#define CHAIN_H

#include <iostream>

template <class T> class Chain; // 전방 선언

template <class T>
class ChainNode 
{
	template <class T> friend class Chain; // friend 선언
private:
	T data;			 // T타입의 데이터를 저장하는 변수
	ChainNode* link; // 연결리스트의 다음 노드를 가리키는 포인터

public:
	ChainNode(T d, ChainNode* next = 0):data(d), link(next){ } // 생성자
};


template <class T>
class Chain
{
private:
	ChainNode<T>* first; // 리스트의 첫번째 노드를 가리키는 포인터
public:
	Chain();		  	 // 생성자

	~Chain() { this->freeAll(); }  // freeAll함수를 호출하는 파괴자

	void freeAll();		 //연결된 모든 ChainNode의 메모리를 해제하는 함수

	void InsertFront(const T& e);  // 데이터 e를 가진 노드 생성하고 리스트에 맨앞에 push한다.

	void NodeSwap(T& e); // 데이터e를 가지고 있는 노드와 그 다음의 노드를 swap하는 함수

	class iterator {	 // 반복자
	private:
		ChainNode<T>* current;	   // 반복자가 나타내는 노드의 주소값을 가지는 변수

	public:
		iterator(ChainNode<T> * startNode = 0) : current(startNode){ } // 생성자

		//역참조 연산자
		T& operator* () const { return current->data; } 
		T* operator->() const { return &current->data; }

		iterator& operator++() { // 사전증가
			current = current->link;
			return *this;
		}
		iterator operator++(int) { // 사후증가
			iterator old = *this;
			current = current->link;
			return old;
		}

		//동등 검사
		bool operator != (const iterator right) const {
			return current != right.current;
		}
		bool operator == (const iterator right) const {
			return current == right.current;
		}
	}; // end of iterator

	iterator begin() // first를 current로 가지는 반복자 반환
	{ 
		return iterator(first);
	}
	iterator end() // NULL을 current로 가지는 반복자 반환
	{
		return iterator(NULL);
	}
};

template <class T>
Chain<T>::Chain() { first = NULL; } // 생성자로 first = 0으로 초기화

template <class T>
void Chain<T>::freeAll()
{
	// 노드의 link를 따라가면서 모든 노드의 메모리 해제
	while (first != NULL) { 
		ChainNode<T>* temp = first;
		first = first->link;
		delete temp;
	}
}

template <class T>
void Chain<T>::InsertFront(const T& e)
{
	// e 데이터를 가지는 새로운 노드 할당함과 동시에 리스트 맨 앞에 push
	first = new ChainNode<T>(e,first);
}

template <class T>
void Chain<T>::NodeSwap(T& e)
{
	ChainNode<T>* current = first, *previous = NULL;// previous는 current를 따라간다.

	while (e != current->data && current != NULL) { // current의 데이터가 인수로 받은 데이터 e와 같거나
		previous = current;							// 혹은 연결 리스트 끝까지 간 경우까지 반복
		current = current->link;
	}

	if (current == NULL) {							// 찾고 있는 노드가 없는 경우
		std::cout << "원하는 노드가 리스트에 없습니다" << std::endl;
		return;
	}

	ChainNode<T>* nextNode = current->link;			// current->link을 가지는 새로운 노드 포인터 선언

	if (current == first) {							// current가 first인 경우
		current->link = nextNode->link;
		nextNode->link = current;
		first = nextNode;
 	}

	else if(nextNode != NULL) {						// current가 마지막 노드가 아닌 경우
		previous->link = nextNode;
		current->link = nextNode->link;
		nextNode->link = current;
	}
} 
#endif
