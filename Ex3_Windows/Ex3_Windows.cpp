// Ex3_Windows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "OopStack.hpp"
extern const char* TestSTACK(int& s);	//����ʵ����
int main()
{
	int score = -1;
	const char* res = TestSTACK(score);
	std::cout << score << std::endl << res << std::endl;
	return 0;
}