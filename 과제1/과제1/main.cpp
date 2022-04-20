#include <iostream>
#include "Rectangle.h"

int main()
{
	Rectangle r1;
	std::cout << "r1 ";
	std::cin >> r1; // r1 객체의 x,y,w,h 값 입력연산자 >>로 입력 받기

	Rectangle r2;
	std::cout << "r2 ";
	std::cin >> r2; // r2 객체의 x,y,w,h 값 입력연산자 >>로 입력 받기

	Rectangle r3;
	r3 = (r1 == r2); // 연산자== 다중화를 통해 r3에 r1과 r2의 공통된 영역 정보를 저장

	std::cout << "r3 객체의 영역" << std::endl;
	r3.Show_area(); //r3의 영역이 존재하면 관련 정보 출력, 존재하지 않으면 존재하지 않다고 출력
	
	return 0;
}