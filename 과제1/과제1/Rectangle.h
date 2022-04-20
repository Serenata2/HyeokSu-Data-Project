#pragma once

#include <iostream>

class Rectangle

{
private:
	int width; // �簢���� ���� ����
	int height; // �簢���� ���� ����
	int xLow, yLow; // �簢���� �����ϴ� �𼭸��� x,y��ǥ

public:
	Rectangle(int x = 0, int y = 0, int w = 0, int h = 0); // default value ���� 0���� �������ش�
	~Rectangle(); // �ı���

	friend std::ostream& operator <<(std::ostream&, Rectangle&); // ��¿����� <<�� ���� �����ε�
	friend std::istream& operator >>(std::istream&, Rectangle&); // �Է¿����� >>�� ���� �����ε� 

	int Find_Common_Area(); // ��ü�� ���̸� ���ϴ� �Լ�
	Rectangle operator ==(Rectangle&); // ��ü ���� ���� �� ������ ��Ÿ���� ���ο� ��ü�� �����ϴ� ������==�� ����ȭ
	void Show_area(); // ��ü�� ������ ����, xLow��ǥ, yLow��ǥ, height, width ���������� ������ �˷��ִ� �Լ�
};