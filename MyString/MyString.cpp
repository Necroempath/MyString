#include <iostream>
#include "string.h"
int main()
{
	string str ("baggar");
	string str1 ("gg");
	//string str1;
	//std::cin >> str1;
	char val = 'ar';
	str.Remove(str1);
	std::cout << str;

	//string str1("asd");
	//bool cmp = str == str1;
	//std::cout << str * 3;
	/*std::cout << (str == str1);
	std::cout << (str == "asd");
	std::cout << (str == "asD");*/
	//std::cout << str << "\n";
	return 0;
}

