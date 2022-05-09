#include <iostream>
#include "Polynomial.h"

int main(void)
{
	float x; // 변수 x 선언
	Polynomial A; // 3개의 다항식 객체 선언
	Polynomial B;
	Polynomial C;
	std::cout << "다항식 A 입력 : ";
	A.Input_Polynomial(); // 다항식 A입력

	std::cout << "다항식 B 입력 : ";
	B.Input_Polynomial(); // 다항식 B입력

	std::cout << "입력 한 식 A : ";
	A.Classify_Polynomial(); // 다항식 A정리
	A.Sort_Polynomial(); // 다항식 A정렬
	A.Show_Polynomial(); // 다항식 A출력

	std::cout << "입력 한 식 B : ";
	B.Classify_Polynomial(); // 다항식 B정리
	B.Sort_Polynomial(); // 다항식 B정렬
	B.Show_Polynomial(); // 다항식 B출력

	std::cout << "A X B = ";
	C.Mul(A, B); // A와 B를 곱한 결과의 다항식을 C에 저장
	C.Classify_Polynomial(); // 다항식 C정리(A, B가 0일 수도 있기에)
	C.Show_Polynomial(); // 다항식 C출력

	std::cout << "대입할 값 x 입력 : ";
	std::cin >> x;
	// A, B, C다항식에 x 값을 대입하고 그 결과를 각각 출력
	std::cout << "결과 : " << "A(" << x << ") = " << A.Eval(x)
		<< ", B(" << x << ") = " << B.Eval(x)
		<< ", C(" << x << ") = " << C.Eval(x) << std::endl;

	return 0;
}