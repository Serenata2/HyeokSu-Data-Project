#pragma once

#include <iostream>
#include <stdio.h>

class Polynomial; // 전방선언

class Term // Term 타입 (계수, 지수) 정의
{
	friend Polynomial; // Term은 Polynomial의 친구!
private:
	float coef; // 계수
	int exp; // 지수, 이때 지수를 자연수라고 가정하자

};

class Polynomial
{
public:
	Polynomial(int c = 1); // 생성자로 capacity의 default value를 1로 해준다
	~Polynomial(); // 파괴자
	void Add(Polynomial& , Polynomial&); // 두 다항식의 덧셈을 구현하는 함수
	void Mul(Polynomial&, Polynomial&); // 두 다항식의 곱셈을 구현하는 함수
	float Eval(float); // *this에 x를 대입한 값을 계산하여 그 결과를 반환하는 함수
	bool NewTerm(const float, const int); // 인수로 계수, 지수를 받고 이를 (*this)의 termArray에 저장하는 함수
	void Show_Polynomial(); // 다항식을 보여주는 함수
	void Classify_Polynomial(); // 다항식을 정리하는 함수
	void Sort_Polynomial(); // 다항식을 차수 순으로 정렬하는 함수
	void Input_Polynomial(); // 다항식을 입력받는 함수
	bool CopyObject(const Polynomial&); // 참조하는 객체를 복사해서 (*this)에 붙여넣는 함수

private:
	Term* termArray; // 클래스 Term으로 된 배열
	int capacity; // termArray의 사이즈
	int terms; // term의 개수
};