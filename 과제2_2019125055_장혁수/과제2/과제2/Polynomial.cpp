#include <iostream>
#include <stdio.h>
#include<stdlib.h> // abs�Լ�(���� �Լ�)�� ����ϱ� ���ؼ�
#include "Polynomial.h"
using namespace std;


Polynomial::Polynomial(int c) // �����ڷ� capacity default value�� 1�� ����
{ // termArray�� ������, ���� ������ ���� c, 0���� �ʱ�ȭ�Ѵ�.
	capacity = c;
	terms = 0;
	termArray = new Term[capacity]; // capacity���̸�ŭ Term �迭 �Ҵ�
}

Polynomial::~Polynomial() // �ı���
{
	delete[] termArray; // �����Ҵ� �� termArray �޸� ����
}

void Polynomial::Add(Polynomial& A, Polynomial& B) // ���׽� A�� ���׽� B�� ���ϴ� �Լ�
{
	int aPos = 0, bPos = 0; // A�� B�� Ž���ؾ��ϴ� ���� index�� ��Ÿ���� ����

	Polynomial C; // �ӽ������� A�� B�� ���� ���� �� Ŭ���� ����
	while ((aPos < A.terms) && (bPos < B.terms)) { // A�� B �� �� �ϳ��� Ž���� ���� �������� ���� ������ �ݺ�
		if (A.termArray[aPos].exp == B.termArray[bPos].exp) { // ���� Ž���ϴ� A,B ���� ���ߴµ� A�� B�� ������ ���� ���
			float t = A.termArray[aPos].coef + B.termArray[bPos].coef; // Ž���ϴ� A�� B ���� ����� ���Ѵ�
			if (t) C.NewTerm(t, A.termArray[aPos].exp); // ���� ���� 0�� �ƴϸ� C�� �߰�
			aPos++, bPos++; // aPos, bPos�� 1 ����
		}
		else if (A.termArray[aPos].exp < B.termArray[bPos].exp) { // Ž���ؾ��ϴ� A, B�� �� B�� �������� A�� ���������� ū ��� 
			C.NewTerm(B.termArray[bPos].coef, B.termArray[bPos].exp); // Ž�� ���� B�� C�� �߰�
			bPos++; //bPos�� 1 ����
		}
		else {                                                 // Ž���ؾ��ϴ� A, B�� �� A�� �������� B�� ���������� ū ���   
			C.NewTerm(A.termArray[aPos].coef, A.termArray[aPos].exp); // Ž�� ���� A�� C�� �߰�
			aPos++; //aPos�� 1 ����
		}
	} // while���� ��

	for (; aPos < A.terms; aPos++) // A�� Ž������ ���� ������ �׵��� �߰��Ѵ�.(�����Ѵٸ�)
		C.NewTerm(A.termArray[aPos].coef, A.termArray[aPos].exp);

	for (; bPos < B.terms; bPos++) // B�� Ž������ ���� ������ �׵��� �߰��Ѵ�.(�����Ѵٸ�)
		C.NewTerm(B.termArray[bPos].coef, B.termArray[bPos].exp);

	CopyObject(C); // CopyObject�Լ��� �Ἥ C�� ������ (*this)�� ����
}

void Polynomial::Mul(Polynomial& A, Polynomial& B) //  ���׽� A�� ���׽� B�� ���ϴ� �Լ�
{
	Polynomial temp(B.terms); // �ӽ������� A�� B�� ���� ���� �� Ŭ���� ����
	temp.terms = B.terms; // ���߿� Add�Լ������� terms ���� ���⿡ temp�� terms���� B.terms ������ �ٲ�

	for (int i = 0; i < A.terms; i++) { // ���׽� A�� �� �ϳ��� ���׽� B�� ��� �װ� ���� ���Ѵ�.
		for (int j = 0; j < B.terms; j++) { // ���׽� B�� ��� �׿� ����
			// ������ ���� �����ְ�, ����� ���� �����ش�.
			temp.termArray[j].exp = A.termArray[i].exp + B.termArray[j].exp;
			temp.termArray[j].coef = A.termArray[i].coef * B.termArray[j].coef;
		}
		this->Add(*this, temp); // Add�Լ��� �̿��� (*this)�� temp�� ���׽��� ���� �ٽ� (*this)�� ����
	}
}

float Polynomial::Eval(float x) // (*this)�� ���׽Ŀ� x ���� �����ϸ� ������ ���� ��ȯ�� �ִ� �Լ�
{
	float total = 0.0f, p = 1.0f; // ��� ������ �����ϴ� ����, �ŵ������� ���� ���� ����
	for (int i = 0; i < terms; i++) {
		p = 1.0f; // p�� 1.0 ���� 
		for (int j = 1; j <= termArray[i].exp; j++) // (X�� i+1��° ���� ���� ��), �ٸ� ���� (x ^ termArray[i].exp)�� ���ϴ� �ݺ���
			p *= x;
		total += (termArray[i].coef) * p; // total���밡 �� �׿� x���� �������� �� ������ ������ ������ �ش�.
	}
	return total; // total ��ȯ
}

bool Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	// �μ��� ���, ������ �ް� (*this)�� termArray�� �����ϴ� �Լ�

	if (terms == capacity) { // ���� �뷮�� ���� ������ ���� ��
		capacity *= 2;  // ����뷮�� �ø���.
		try
		{
			Term* temp = new Term[capacity]; // ���� ����뷮�� 2�踸ŭ ������ Term�迭�� �����Ҵ�
			std::copy(termArray, termArray + terms, temp); // ���� ���� �迭�� termArray �� ����
			delete[] termArray; // ���� termArray�� �����Ҵ� �� �޸� ����
			termArray = temp; //  termArray�� ���� �����Ҵ� �� Term�迭 ����Ű�� ��
		}
		catch (const std::bad_alloc& e) // �����Ҵ翡 ������ ���
		{
			std::cout << "Error! �����Ҵ翡 �����Ͽ����ϴ�!" << std::endl;
			exit(1); // ���α׷� ����
		}
	}

	termArray[terms].coef = theCoeff; // termArray�� �μ��� ���� ��� ���� �� ����
	termArray[terms++].exp = theExp;
	return 1; // �Լ��� ���������� �۵��ؼ� true ��ȯ
}

void Polynomial::Show_Polynomial() // ���׽��� ����ڰ� ���� ���� �����ִ� �Լ�
{
	// ���� ���� �ϳ��� ���, ���� 2�� �̻��� ���� ������.
	if (terms == 1)                                           // ���� �ϳ� �� ���
		if (termArray[0].exp == 0) // ����� ���
			std::cout << termArray[0].coef;
		else if (termArray[0].coef == 1.0f) // ����� 1�� ���
			std::cout << "x^" << termArray[0].exp;
		else if (termArray[0].coef == -1.0f) // ����� -1�� ���
			std::cout << "-x^" << termArray[0].exp;
		else // ������ ���
			std::cout << termArray[0].coef << "x^" << termArray[0].exp;

	else {                                                   // ���� �������� ���
		int i = 0;
		while (i < terms - 1) { // ù° �׺��� ������ �� �ױ��� ���
			if (i == 0)   // ù��° �׿� ������ ���� �� ���� ���
				if (termArray[i].coef == 1.0f) // ����� 1�� ���
					std::cout << "x^" << termArray[i].exp;
				else if (termArray[i].coef == -1.0f) // ����� -1�� ���
					std::wcout << "-x^" << termArray[i].exp;
				else // ������ ���
					std::cout << termArray[i].coef << "x^" << termArray[i].exp;

			else // �ι�° �׺��� ������ ������ �׿� ������ ���� �� ���� ���
				if (abs(termArray[i].coef) == 1.0f) // ����� 1, -1�� ���
					std::cout << "x^" << termArray[i].exp;
				else // ������ ���
					std::cout << abs(termArray[i].coef) << "x^" << termArray[i].exp;

			if (termArray[i + 1].coef > 0.0f) // ���� ���� ��ȣ �̸� ���
				std::cout << " + ";
			else
				std::cout << " - ";
			i++; // i �� 1 ����
		} // while�� ��

		// ������ �� ���
		if (termArray[i].exp == 0) // ����� ���
			std::cout << abs(termArray[i].coef);
		else if (abs(termArray[i].coef) == 1.0f) // ����� 1 �Ǵ� -1�� ���
			std::cout << "x^" << termArray[i].exp; // �տ��� �̹� ��ȣ�� �ٿ��� ������ "x^"�� ����Ѵ�
		else
			std::cout << abs(termArray[i].coef) << "x^" << termArray[i].exp;
	} // else�� ��

	std::cout << std::endl;
}


void Polynomial::Classify_Polynomial() // ���׽��� ���� ���ִ� �Լ�(������ x)
{
	// ���� ��� ������ ���� ���� 2�� �����ϸ� �� �� ���� ���ؼ� �ϳ��� ������ ������ش�

	int k = 0; // ���Ӱ� ����� ���� ������ �����ϴ� ����
	float Coef_Sum = 0.0f; // ����� ���� �����ϴ� ����
	Polynomial P(terms); // (*this)�� term������ŭ�� Term�迭 ���̸� ������ �ִ� ��ü P ����

	for (int i = 0; i < terms; i++) { // �ϴ� (*this) ��ü�� ��� �׿� ����
		if (termArray[i].exp == -1) // ���࿡ ������ ���� -1�̸� �̹� ���Ҵ� ���̹Ƿ� �н�
			continue;
		Coef_Sum = termArray[i].coef; // ���� index i ���� ����� ����
		for (int j = i + 1; j < terms; j++) { // index�� i���� ū �׵鿡�� ���� 
			if (termArray[i].exp == termArray[j].exp) { // ������ ���� ������ index i ���� ������ ������
				Coef_Sum += termArray[j].coef; // Coef_sum������ ������ ���� ����� ����
				termArray[j].exp = -1; // Ȯ���� ���̹Ƿ� �� ���� ������ -1�� ����
			}
		}
		if (Coef_Sum == 0.0f) // ������� 0 �ΰ��
			continue; // �������� �ʰ� �н�
		P.termArray[k].coef = Coef_Sum; // ���� P�� termArray �տ������� ���ʴ�� ����
		P.termArray[k++].exp = termArray[i].exp; // k �� 1 ����
	}

	if (k == 0) { // ���׽��� 0�� ���, P�� termArrya�� �ƹ��͵� ������� ���� ���
		P.capacity = P.terms = 1; // P�� capacity�� terms���� 1�� ����
		P.termArray[0].coef = 0.0f; // ù��° ���� ���, ���� ���� 0���� �ʱ�ȭ
		P.termArray[0].exp = 0;
	}

	else // ������ ���
		P.capacity = P.terms = k; // P�� capacity�� terms ���� k�� �ٲپ��ش�

	this->CopyObject(P); // ���� ���׽� P�� ������ ���� �����ؼ� (*this) ��ü�� ����

}

void Polynomial::Sort_Polynomial()
{
	// ���׽��� ������ ū ������� �����ϴ� �Լ�

	for (int i = 0; i < terms; i++) {
		int j = i; // 
		for (int k = i + 1; k < terms; k++) // termArray[i]�� termArray[terms-1]������ ���� ū ���� ã��
			if (termArray[k].exp > termArray[j].exp) j = k;  // �׸��� ������ ���� ū ���� index�� j�� ����
		std::swap(termArray[i], termArray[j]); // termArray[i], termArray[j] �� ���� ��ȯ
	}
}


void Polynomial::Input_Polynomial() //  ���׽��� �Է��ϴ� �Լ�
{
	float new_coef;
	int new_exp; // �Է¹��� ���, ������ �����ϴ� ����

	do { // 2���� ���� �Է� �޾� �����ϰ�, New_Term�Լ��� �̿��� termArray�� ����
		std::cin >> new_coef >> new_exp;
		this->NewTerm(new_coef, new_exp);
	} while (getchar() != '\n'); // enter�� ĥ ������ �ݺ�
}

bool Polynomial::CopyObject(const Polynomial& P) // P�� ���׽� ������ �����ؼ� (*this)���׽Ŀ� �ٿ��ִ� �Լ�
{
	// �����Ҵ�� PolynomialŬ������ ���Կ����ڸ� �׳� �� �� ���⿡ ���� �Լ��� �������.

	delete[] termArray; // ������ �ִ� termArray�� �����Ҵ�� �޸𸮸� �����Ѵ�.

	try
	{
		termArray = new Term[P.terms]; // �����ϴ� ��ü P�� ���� ������ŭ�� ������ Term�迭�� �����Ҵ� �Ѵ�.
	}
	catch (const std::bad_alloc& e) // �����Ҵ翡 ������ ���
	{
		std::cout << "Error! �����Ҵ翡 �����Ͽ����ϴ�!" << std::endl;
		exit(1); // ���α׷� ����
	}

	capacity = terms = P.terms; // ��ü p�� terms���� (*this)�� terms, capacity�� ���� ����
	std::copy(P.termArray, P.termArray + P.terms, termArray); // (*this)�� P�� termArray�� ���� ����
	return 1; // �Լ��� ���������� �۵��ؼ� true ��ȯ
}
