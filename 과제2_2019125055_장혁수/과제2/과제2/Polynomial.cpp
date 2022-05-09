#include <iostream>
#include <stdio.h>
#include<stdlib.h> // abs함수(절댓값 함수)를 사용하기 위해서
#include "Polynomial.h"
using namespace std;


Polynomial::Polynomial(int c) // 생성자로 capacity default value를 1로 지정
{ // termArray의 사이즈, 항의 개수를 각각 c, 0으로 초기화한다.
	capacity = c;
	terms = 0;
	termArray = new Term[capacity]; // capacity길이만큼 Term 배열 할당
}

Polynomial::~Polynomial() // 파괴자
{
	delete[] termArray; // 동적할당 된 termArray 메모리 해제
}

void Polynomial::Add(Polynomial& A, Polynomial& B) // 다항식 A와 다항식 B를 더하는 함수
{
	int aPos = 0, bPos = 0; // A와 B의 탐색해야하는 항의 index를 나타내는 변수

	Polynomial C; // 임시적으로 A와 B의 합을 저장 할 클래스 선언
	while ((aPos < A.terms) && (bPos < B.terms)) { // A와 B 둘 중 하나라도 탐색할 항이 남아있지 않은 경우까지 반복
		if (A.termArray[aPos].exp == B.termArray[bPos].exp) { // 만약 탐색하는 A,B 항을 비교했는데 A와 B의 지수가 같은 경우
			float t = A.termArray[aPos].coef + B.termArray[bPos].coef; // 탐색하는 A와 B 항의 계수를 더한다
			if (t) C.NewTerm(t, A.termArray[aPos].exp); // 더한 값이 0이 아니면 C에 추가
			aPos++, bPos++; // aPos, bPos값 1 증가
		}
		else if (A.termArray[aPos].exp < B.termArray[bPos].exp) { // 탐색해야하는 A, B항 중 B의 지수값이 A의 지수값보다 큰 경우 
			C.NewTerm(B.termArray[bPos].coef, B.termArray[bPos].exp); // 탐색 중인 B항 C에 추가
			bPos++; //bPos값 1 증가
		}
		else {                                                 // 탐색해야하는 A, B항 중 A의 지수값이 B의 지수값보다 큰 경우   
			C.NewTerm(A.termArray[aPos].coef, A.termArray[aPos].exp); // 탐색 중인 A항 C에 추가
			aPos++; //aPos값 1 증가
		}
	} // while문의 끝

	for (; aPos < A.terms; aPos++) // A의 탐색하지 않은 나머지 항들을 추가한다.(존재한다면)
		C.NewTerm(A.termArray[aPos].coef, A.termArray[aPos].exp);

	for (; bPos < B.terms; bPos++) // B의 탐색하지 않은 나머지 항들을 추가한다.(존재한다면)
		C.NewTerm(B.termArray[bPos].coef, B.termArray[bPos].exp);

	CopyObject(C); // CopyObject함수를 써서 C의 내용을 (*this)에 저장
}

void Polynomial::Mul(Polynomial& A, Polynomial& B) //  다항식 A와 다항식 B를 곱하는 함수
{
	Polynomial temp(B.terms); // 임시적으로 A와 B의 곱을 저장 할 클래스 선언
	temp.terms = B.terms; // 나중에 Add함수에서는 terms 값만 보기에 temp의 terms값만 B.terms 값으로 바꿈

	for (int i = 0; i < A.terms; i++) { // 다항식 A의 항 하나씩 다항식 B의 모든 항과 각각 곱한다.
		for (int j = 0; j < B.terms; j++) { // 다항식 B의 모든 항에 접근
			// 지수는 서로 더해주고, 계수는 서로 곱해준다.
			temp.termArray[j].exp = A.termArray[i].exp + B.termArray[j].exp;
			temp.termArray[j].coef = A.termArray[i].coef * B.termArray[j].coef;
		}
		this->Add(*this, temp); // Add함수를 이용해 (*this)와 temp의 다항식의 합을 다시 (*this)에 저장
	}
}

float Polynomial::Eval(float x) // (*this)의 다항식에 x 값을 대입하면 나오는 값을 반환해 주는 함수
{
	float total = 0.0f, p = 1.0f; // 결과 값들을 저장하는 변수, 거듭제곱에 쓰일 변수 선언
	for (int i = 0; i < terms; i++) {
		p = 1.0f; // p에 1.0 대입 
		for (int j = 1; j <= termArray[i].exp; j++) // (X의 i+1번째 항의 지수 승), 다른 말로 (x ^ termArray[i].exp)을 구하는 반복문
			p *= x;
		total += (termArray[i].coef) * p; // total에대가 각 항에 x값을 대입했을 때 나오는 값들을 저장해 준다.
	}
	return total; // total 반환
}

bool Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	// 인수로 계수, 지수를 받고 (*this)의 termArray에 저장하는 함수

	if (terms == capacity) { // 저장 용량이 항의 개수와 같을 때
		capacity *= 2;  // 저장용량을 늘린다.
		try
		{
			Term* temp = new Term[capacity]; // 기존 저장용량의 2배만큼 길이의 Term배열을 동적할당
			std::copy(termArray, termArray + terms, temp); // 새로 만든 배열에 termArray 값 복사
			delete[] termArray; // 기존 termArray에 동적할당 된 메모리 해제
			termArray = temp; //  termArray가 새로 동적할당 된 Term배열 가리키게 함
		}
		catch (const std::bad_alloc& e) // 동적할당에 실패한 경우
		{
			std::cout << "Error! 동적할당에 실패하였습니다!" << std::endl;
			exit(1); // 프로그램 종료
		}
	}

	termArray[terms].coef = theCoeff; // termArray에 인수로 받은 계수 지수 값 저장
	termArray[terms++].exp = theExp;
	return 1; // 함수가 정상적으로 작동해서 true 반환
}

void Polynomial::Show_Polynomial() // 다항식을 사용자가 보기 좋게 보여주는 함수
{
	// 먼저 항이 하나인 경우, 항이 2개 이상인 경우로 나눈다.
	if (terms == 1)                                           // 항이 하나 인 경우
		if (termArray[0].exp == 0) // 상수인 경우
			std::cout << termArray[0].coef;
		else if (termArray[0].coef == 1.0f) // 계수가 1인 경우
			std::cout << "x^" << termArray[0].exp;
		else if (termArray[0].coef == -1.0f) // 계수가 -1인 경우
			std::cout << "-x^" << termArray[0].exp;
		else // 나머지 경우
			std::cout << termArray[0].coef << "x^" << termArray[0].exp;

	else {                                                   // 항이 여러개인 경우
		int i = 0;
		while (i < terms - 1) { // 첫째 항부터 마지막 전 항까지 출력
			if (i == 0)   // 첫번째 항에 접근한 경우로 그 내용 출력
				if (termArray[i].coef == 1.0f) // 계수가 1인 경우
					std::cout << "x^" << termArray[i].exp;
				else if (termArray[i].coef == -1.0f) // 계수가 -1인 경우
					std::wcout << "-x^" << termArray[i].exp;
				else // 나머지 경우
					std::cout << termArray[i].coef << "x^" << termArray[i].exp;

			else // 두번째 항부터 마지막 전까지 항에 접근한 경우로 그 내용 출력
				if (abs(termArray[i].coef) == 1.0f) // 계수가 1, -1인 경우
					std::cout << "x^" << termArray[i].exp;
				else // 나머지 경우
					std::cout << abs(termArray[i].coef) << "x^" << termArray[i].exp;

			if (termArray[i + 1].coef > 0.0f) // 다음 항의 부호 미리 출력
				std::cout << " + ";
			else
				std::cout << " - ";
			i++; // i 값 1 증가
		} // while문 끝

		// 마지막 항 출력
		if (termArray[i].exp == 0) // 상수인 경우
			std::cout << abs(termArray[i].coef);
		else if (abs(termArray[i].coef) == 1.0f) // 계수가 1 또는 -1인 경우
			std::cout << "x^" << termArray[i].exp; // 앞에서 이미 부호를 붙였기 때문에 "x^"를 출력한다
		else
			std::cout << abs(termArray[i].coef) << "x^" << termArray[i].exp;
	} // else문 끝

	std::cout << std::endl;
}


void Polynomial::Classify_Polynomial() // 다항식을 정리 해주는 함수(정렬은 x)
{
	// 예를 들어 지수가 같은 항이 2개 존재하면 그 두 항을 더해서 하나의 항으로 만들어준다

	int k = 0; // 새롭게 저장된 항의 개수를 저장하는 변수
	float Coef_Sum = 0.0f; // 계수의 합을 저장하는 변수
	Polynomial P(terms); // (*this)의 term개수만큼의 Term배열 길이를 가지고 있는 객체 P 생성

	for (int i = 0; i < terms; i++) { // 일단 (*this) 객체의 모든 항에 접근
		if (termArray[i].exp == -1) // 만약에 지수의 값이 -1이면 이미 보았던 항이므로 패스
			continue;
		Coef_Sum = termArray[i].coef; // 먼저 index i 항의 계수를 저장
		for (int j = i + 1; j < terms; j++) { // index가 i보다 큰 항들에게 접근 
			if (termArray[i].exp == termArray[j].exp) { // 접근한 항의 지수와 index i 항의 지수가 같으면
				Coef_Sum += termArray[j].coef; // Coef_sum변수에 접근한 항의 계수를 더함
				termArray[j].exp = -1; // 확인한 항이므로 그 항의 지수에 -1값 대입
			}
		}
		if (Coef_Sum == 0.0f) // 계수합이 0 인경우
			continue; // 저장하지 않고 패스
		P.termArray[k].coef = Coef_Sum; // 이후 P의 termArray 앞에서부터 차례대로 저장
		P.termArray[k++].exp = termArray[i].exp; // k 값 1 증가
	}

	if (k == 0) { // 다항식이 0인 경우, P의 termArrya에 아무것도 저장되지 않은 경우
		P.capacity = P.terms = 1; // P의 capacity와 terms값은 1로 저장
		P.termArray[0].coef = 0.0f; // 첫번째 항의 계수, 지수 값을 0으로 초기화
		P.termArray[0].exp = 0;
	}

	else // 나머지 경우
		P.capacity = P.terms = k; // P의 capacity와 terms 값을 k로 바꾸어준다

	this->CopyObject(P); // 이후 다항식 P의 데이터 값을 복사해서 (*this) 객체에 저장

}

void Polynomial::Sort_Polynomial()
{
	// 다항식을 차수가 큰 순서대로 정렬하는 함수

	for (int i = 0; i < terms; i++) {
		int j = i; // 
		for (int k = i + 1; k < terms; k++) // termArray[i]와 termArray[terms-1]사이의 가장 큰 차수 찾음
			if (termArray[k].exp > termArray[j].exp) j = k;  // 그리고 차수가 가장 큰 항의 index를 j에 저장
		std::swap(termArray[i], termArray[j]); // termArray[i], termArray[j] 값 서로 교환
	}
}


void Polynomial::Input_Polynomial() //  다항식을 입력하는 함수
{
	float new_coef;
	int new_exp; // 입력받은 계수, 지수를 저장하는 변수

	do { // 2개씩 값을 입력 받아 저장하고, New_Term함수를 이용해 termArray에 저장
		std::cin >> new_coef >> new_exp;
		this->NewTerm(new_coef, new_exp);
	} while (getchar() != '\n'); // enter를 칠 때까지 반복
}

bool Polynomial::CopyObject(const Polynomial& P) // P의 다항식 내용을 복사해서 (*this)다항식에 붙여넣는 함수
{
	// 동적할당된 Polynomial클래스는 대입연산자를 그냥 쓸 수 없기에 따로 함수를 만들었다.

	delete[] termArray; // 기존에 있던 termArray의 동적할당된 메모리를 해제한다.

	try
	{
		termArray = new Term[P.terms]; // 참조하는 객체 P의 항의 개수만큼의 길이의 Term배열을 동적할당 한다.
	}
	catch (const std::bad_alloc& e) // 동적할당에 실패한 경우
	{
		std::cout << "Error! 동적할당에 실패하였습니다!" << std::endl;
		exit(1); // 프로그램 종료
	}

	capacity = terms = P.terms; // 객체 p의 terms값을 (*this)의 terms, capacity에 각각 저장
	std::copy(P.termArray, P.termArray + P.terms, termArray); // (*this)에 P의 termArray의 내용 복사
	return 1; // 함수가 정상적으로 작동해서 true 반환
}
