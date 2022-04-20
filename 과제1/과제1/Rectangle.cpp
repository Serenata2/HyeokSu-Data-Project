#include "Rectangle.h"
#include <iostream>
//using namespace std;


Rectangle::Rectangle(int x, int y, int w, int h) { // 생성자
	xLow = x;                        // default value를 각각 0으로 지정해주었다.
	yLow = y;
	width = w;
	height = h;
}

Rectangle::~Rectangle() { }

std::ostream& operator <<(std::ostream& os, Rectangle& r) { // 연산자 <<에 대한 오버로딩
	os << "height : " << r.height << std::endl
		<< "width : " << r.width << std::endl
		<< "x : " << r.xLow << std::endl
		<< "y : " << r.yLow << std::endl;

	return os;
}

std::istream& operator >>(std::istream& in, Rectangle& r) {  // 입력연산자 >>에 대한 오버로딩 
	std::cout << "객체의 다음 값들을 입력하세요" << std::endl << "height : ";
	in >> r.height;
	std::cout << "width : ";
	in >> r.width;
	std::cout << "x : ";
	in >> r.xLow;
	std::cout << "y : ";
	in >> r.yLow;
	std::cout << std::endl;

	return in;
}

int Rectangle::Find_Common_Area() {
	return height * width; // (*this)의 높이와 너비를 곱해서 넓이를 리턴
}

Rectangle Rectangle::operator ==(Rectangle& r) {
	Rectangle *big; // 두 객채의 xLow 혹은 yLow를 비교해서 더 큰 값을 가지고 있는 객체의 주소값을 가지는 포인터 변수
	Rectangle *small; // 두 객채의 xLow 혹은 yLow를 비교해서 더 작은 값을 가지고 있는 객체의 주소값을 가지는 포인터 변수
	int big_x; // 두 객체의 더 큰 xLow를 저장하는 변수
	int common_w, common_h; // 두 객체의 공통 영역의 너비, 높이를 저장하는 변수 

	if (r.xLow >= xLow) {  // 먼저 xLow값을 비교해서 큰 객체의 주소값은 big에 작은 객체의 주소값은 samll에 넣어준다
		big = &r;
		small = this;
	}
	else {
		big = this;
		small = &r;
	}

	// 한 객체의 너비영역이 다른 객체의 너비영역을 포함하지 않는 경우로
	// 공통 너비영역은 작은 xLow를 가지고 있는 객체의 xLow + width에서 다른 객체의 xLow를 뺀 값이다.
	if (small->xLow + small->width <= big->xLow + big->width) { 
		common_w = small->xLow + small->width - big->xLow; 
	}
	else // 한 객체의 너비영역이 다른 객체의 너비영역을 포함하는 경우
		common_w = big->width; // 공통 너비영역은 큰 xLow를 가지고 있는 객체의 width이다.
	big_x = big->xLow; // big의 값을 변경할 예정이므로 big_x에 따로 저장


	if (r.yLow >= yLow) {  // 다음 yLow값을 비교해서 큰 객체의 주소값은 big에 작은 객체의 주소값은 samll에 넣어준다
		big = &r;
		small = this;
	}
	else {
		big = this;
		small = &r;
	}

	// 한 객체의 높이영역이 다른 객체의 높이영역을 완전히 포함하지 않는 경우로
	// 공통 높이영역은 작은 yLow를 가지고 있는 객체의 yLow + height에서 다른 객체의 yLow를 뺀 값이다.
	if (small->yLow + small->height < big->yLow + big->height) { 
		common_h = small->yLow + small->height - big->yLow; 
	}
	else // 한 객체의 높이영역이 다른 객체의 높이영역을 완전히 포함하는 경우
		common_h = big->height; // 공통 높이영역은 큰 yLow를 가지고 있는 객체의 height이다.

	// 이후 새로운 Rectangle 객체를 만드는데 큰 xLow값, 큰 yLow값, commn_w, common_y값으로 초기화해주고 반환한다.
	// 이때 common_w와 common_h 둘 중에 하나라도 0보다 작거나 같으면 공통된 영역은 없다.
	return Rectangle(big_x, big->yLow, common_w, common_h);
}

void Rectangle::Show_area() {
	if (width > 0 && height > 0) { // 영역이 존재하는 경우
		std::cout << *this; // 연산자 <<에 대한 오버로딩을 이용해 객체의 데이터 멤버 값들 출력
		std::cout << "넓이 : " << this->Find_Common_Area() << std::endl << std::endl; // 클래스 내 넓이 찾는 함수를 이용해 영역의 넓이 출력
	}
	else // 영역이 존재하지 않는 경우
		std::cout << "영역이 존재하지 않습니다." << std::endl << std::endl;
}