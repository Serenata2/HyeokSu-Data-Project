#include <iostream>
#include "Polynomial.h"

int main(void)
{
	float x; // ���� x ����
	Polynomial A; // 3���� ���׽� ��ü ����
	Polynomial B;
	Polynomial C;
	std::cout << "���׽� A �Է� : ";
	A.Input_Polynomial(); // ���׽� A�Է�

	std::cout << "���׽� B �Է� : ";
	B.Input_Polynomial(); // ���׽� B�Է�

	std::cout << "�Է� �� �� A : ";
	A.Classify_Polynomial(); // ���׽� A����
	A.Sort_Polynomial(); // ���׽� A����
	A.Show_Polynomial(); // ���׽� A���

	std::cout << "�Է� �� �� B : ";
	B.Classify_Polynomial(); // ���׽� B����
	B.Sort_Polynomial(); // ���׽� B����
	B.Show_Polynomial(); // ���׽� B���

	std::cout << "A X B = ";
	C.Mul(A, B); // A�� B�� ���� ����� ���׽��� C�� ����
	C.Classify_Polynomial(); // ���׽� C����(A, B�� 0�� ���� �ֱ⿡)
	C.Show_Polynomial(); // ���׽� C���

	std::cout << "������ �� x �Է� : ";
	std::cin >> x;
	// A, B, C���׽Ŀ� x ���� �����ϰ� �� ����� ���� ���
	std::cout << "��� : " << "A(" << x << ") = " << A.Eval(x)
		<< ", B(" << x << ") = " << B.Eval(x)
		<< ", C(" << x << ") = " << C.Eval(x) << std::endl;

	return 0;
}