#pragma once

#include <iostream>

class Rectangle

{
private:
	int width; // 사각형의 가로 길이
	int height; // 사각형의 세로 길이
	int xLow, yLow; // 사각형의 왼쪽하단 모서리의 x,y좌표

public:
	Rectangle(int x = 0, int y = 0, int w = 0, int h = 0); // default value 각각 0으로 지정해준다
	~Rectangle(); // 파괴자

	friend std::ostream& operator <<(std::ostream&, Rectangle&); // 출력연산자 <<에 대한 오버로딩
	friend std::istream& operator >>(std::istream&, Rectangle&); // 입력연산자 >>에 대한 오버로딩 

	int Find_Common_Area(); // 객체의 넓이를 구하는 함수
	Rectangle operator ==(Rectangle&); // 객체 간에 공통 된 영역을 나타내는 새로운 객체를 생성하는 연산자==의 다중화
	void Show_area(); // 객체의 영역의 넓이, xLow좌표, yLow좌표, height, width 보여줌으로 영역을 알려주는 함수
};