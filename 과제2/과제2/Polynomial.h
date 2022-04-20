#pragma once

#include <iostream>
#include <stdio.h>

class Polynomial; // ���漱��

class Term // Term Ÿ�� (���, ����) ����
{
	friend Polynomial; // Term�� Polynomial�� ģ��!
private:
	float coef; // ���
	int exp; // ����, �̶� ������ �ڿ������ ��������

};

class Polynomial
{
public:
	Polynomial(int c = 1); // �����ڷ� capacity�� default value�� 1�� ���ش�
	~Polynomial(); // �ı���
	void Add(Polynomial& , Polynomial&); // �� ���׽��� ������ �����ϴ� �Լ�
	void Mul(Polynomial&, Polynomial&); // �� ���׽��� ������ �����ϴ� �Լ�
	float Eval(float); // *this�� x�� ������ ���� ����Ͽ� �� ����� ��ȯ�ϴ� �Լ�
	bool NewTerm(const float, const int); // �μ��� ���, ������ �ް� �̸� (*this)�� termArray�� �����ϴ� �Լ�
	void Show_Polynomial(); // ���׽��� �����ִ� �Լ�
	void Classify_Polynomial(); // ���׽��� �����ϴ� �Լ�
	void Sort_Polynomial(); // ���׽��� ���� ������ �����ϴ� �Լ�
	void Input_Polynomial(); // ���׽��� �Է¹޴� �Լ�
	bool CopyObject(const Polynomial&); // �����ϴ� ��ü�� �����ؼ� (*this)�� �ٿ��ִ� �Լ�

private:
	Term* termArray; // Ŭ���� Term���� �� �迭
	int capacity; // termArray�� ������
	int terms; // term�� ����
};