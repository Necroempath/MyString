#include "string.h"
#define ascending_factor 2.0f
#define descending_factor .7f

string::string() { Default(); }

string::string(const char* str)
{
	if (!str)
	{
		Default();
		return;
	}

	strcpy(str);
}

string::string(const size_t len)
{
	if (len > 0) {
		_len = len;
		_capacity = _len * ascending_factor;
		_string = new char[_capacity];
	}
	else Default();
}

string::string(const string& other)
{
	if (!other._string)
	{
		Default();
		return;
	}

	strcpy(other._string);
}

string::string(string&& other) noexcept { Init(other); other._string = nullptr; }

string& string::operator=(const string& other)
{
	strcpy(other._string);
	return *this;
}

string& string::operator=(string&& other) noexcept
{
	if (this == &other || !other._string) return *this;

	delete[] _string;

	Init(other);

	other._string = nullptr;
	return *this;
}

string& string::operator=(const char* str)
{
	strcpy(str);
	return *this;
}

string string::operator+(const string& str)
{
	string temp(*this);
	strcat(temp, str._string);

	return temp;
}

string string::operator+(const char* str)
{
	string temp(*this);
	strcat(temp, str);

	return temp;
}

const char string::operator[](const size_t index) const
{
	if (index >= 0 && index < _len)	return _string[index];
}

char& string::operator[](size_t index)
{
	if (index >= 0 && index < _len)	return _string[index];
}

std::ostream& operator<<(std::ostream& os, const string& str)
{
	os << str._string;
	return os;
}

std::istream& operator>>(std::istream& is, string& str)
{
	char* _str = new char[100];
	is >> _str;
	str = _str;

	return is;
}

void string::Default()
{
	_string = nullptr;
	_len = 0;
	_capacity = 0;
}

void string::Init(const string& str)
{
	_string = str._string;
	_len = str._len;
	_capacity = str._capacity;
}

void string::strcpy(const char* source)
{
	if (_string == source || !source) return;

	_len = strlen(source);
	_capacity = _len * ascending_factor;

	delete[] _string;
	_string = new char[_capacity];

	for (size_t i = 0; i < _len; i++)
	{
		_string[i] = source[i];
	}

	_string[_len] = '\0';
}

void string::strcat(string& dest, const char* source) const
{
	size_t len = dest._len + strlen(source);
	dest._capacity = len * ascending_factor;

	char* str = new char[dest._capacity];
	
	for (size_t i = 0; i < dest._len; i++)
	{
		str[i] = dest._string[i];
	}

	for (size_t i = dest._len, j = 0; i < len; i++, j++)
	{
		str[i] = source[j];
	}
	str[len] = '\0';

	dest._len = len;
	delete[] dest._string;
	dest._string = str;
}

void string::ResizeString(const float factor)
{
	_capacity *= factor;

	char* temp = new char[_capacity];

	for (size_t i = 0; i < _len; i++)
	{
		temp[i] = _string[i];
	}

	delete[] _string;
	_string = temp;
}

size_t string::Lenght() { return _len; }

string::~string()
{
	delete[] _string;
}

size_t strlen(const char* str)
{
	size_t size = 0;

	while (str[size]) size++;

	return size;
}



