#include "Rectangle.h"
#include <iostream>
//using namespace std;


Rectangle::Rectangle(int x, int y, int w, int h) { // ������
	xLow = x;                        // default value�� ���� 0���� �������־���.
	yLow = y;
	width = w;
	height = h;
}

Rectangle::~Rectangle() { }

std::ostream& operator <<(std::ostream& os, Rectangle& r) { // ������ <<�� ���� �����ε�
	os << "height : " << r.height << std::endl
		<< "width : " << r.width << std::endl
		<< "x : " << r.xLow << std::endl
		<< "y : " << r.yLow << std::endl;

	return os;
}

std::istream& operator >>(std::istream& in, Rectangle& r) {  // �Է¿����� >>�� ���� �����ε� 
	std::cout << "��ü�� ���� ������ �Է��ϼ���" << std::endl << "height : ";
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
	return height * width; // (*this)�� ���̿� �ʺ� ���ؼ� ���̸� ����
}

Rectangle Rectangle::operator ==(Rectangle& r) {
	Rectangle *big; // �� ��ä�� xLow Ȥ�� yLow�� ���ؼ� �� ū ���� ������ �ִ� ��ü�� �ּҰ��� ������ ������ ����
	Rectangle *small; // �� ��ä�� xLow Ȥ�� yLow�� ���ؼ� �� ���� ���� ������ �ִ� ��ü�� �ּҰ��� ������ ������ ����
	int big_x; // �� ��ü�� �� ū xLow�� �����ϴ� ����
	int common_w, common_h; // �� ��ü�� ���� ������ �ʺ�, ���̸� �����ϴ� ���� 

	if (r.xLow >= xLow) {  // ���� xLow���� ���ؼ� ū ��ü�� �ּҰ��� big�� ���� ��ü�� �ּҰ��� samll�� �־��ش�
		big = &r;
		small = this;
	}
	else {
		big = this;
		small = &r;
	}

	// �� ��ü�� �ʺ񿵿��� �ٸ� ��ü�� �ʺ񿵿��� �������� �ʴ� ����
	// ���� �ʺ񿵿��� ���� xLow�� ������ �ִ� ��ü�� xLow + width���� �ٸ� ��ü�� xLow�� �� ���̴�.
	if (small->xLow + small->width <= big->xLow + big->width) { 
		common_w = small->xLow + small->width - big->xLow; 
	}
	else // �� ��ü�� �ʺ񿵿��� �ٸ� ��ü�� �ʺ񿵿��� �����ϴ� ���
		common_w = big->width; // ���� �ʺ񿵿��� ū xLow�� ������ �ִ� ��ü�� width�̴�.
	big_x = big->xLow; // big�� ���� ������ �����̹Ƿ� big_x�� ���� ����


	if (r.yLow >= yLow) {  // ���� yLow���� ���ؼ� ū ��ü�� �ּҰ��� big�� ���� ��ü�� �ּҰ��� samll�� �־��ش�
		big = &r;
		small = this;
	}
	else {
		big = this;
		small = &r;
	}

	// �� ��ü�� ���̿����� �ٸ� ��ü�� ���̿����� ������ �������� �ʴ� ����
	// ���� ���̿����� ���� yLow�� ������ �ִ� ��ü�� yLow + height���� �ٸ� ��ü�� yLow�� �� ���̴�.
	if (small->yLow + small->height < big->yLow + big->height) { 
		common_h = small->yLow + small->height - big->yLow; 
	}
	else // �� ��ü�� ���̿����� �ٸ� ��ü�� ���̿����� ������ �����ϴ� ���
		common_h = big->height; // ���� ���̿����� ū yLow�� ������ �ִ� ��ü�� height�̴�.

	// ���� ���ο� Rectangle ��ü�� ����µ� ū xLow��, ū yLow��, commn_w, common_y������ �ʱ�ȭ���ְ� ��ȯ�Ѵ�.
	// �̶� common_w�� common_h �� �߿� �ϳ��� 0���� �۰ų� ������ ����� ������ ����.
	return Rectangle(big_x, big->yLow, common_w, common_h);
}

void Rectangle::Show_area() {
	if (width > 0 && height > 0) { // ������ �����ϴ� ���
		std::cout << *this; // ������ <<�� ���� �����ε��� �̿��� ��ü�� ������ ��� ���� ���
		std::cout << "���� : " << this->Find_Common_Area() << std::endl << std::endl; // Ŭ���� �� ���� ã�� �Լ��� �̿��� ������ ���� ���
	}
	else // ������ �������� �ʴ� ���
		std::cout << "������ �������� �ʽ��ϴ�." << std::endl << std::endl;
}