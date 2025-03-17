#include <iostream>
#include "string.h"
int main()
{
	string str;
	std::cin >> str;
	string str1("asd");
	//bool cmp = str == str1;
	std::cout << (str == str1);
	std::cout << (str == "asd");
	std::cout << (str == "asD");
	//std::cout << str << "\n";
	return 0;
}

