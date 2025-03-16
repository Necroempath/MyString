#include <iostream>
#include "string.h"
int main()
{
	string str;
	std::cin >> str;
	//str + " new str";
	str = str + " new str";
	std::cout << str + "s" << "\n";
	std::cout << str << "\n";
	return 0;
}

