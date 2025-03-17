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

	copy(str);
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

	copy(other._string);
}

string::string(string&& other) noexcept { Init(other); other._string = nullptr; }

string& string::operator=(const string& other)
{
	copy(other._string);
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
	copy(str);
	return *this;
}

string string::operator+(const string& str)
{
	string temp(*this);
	concat(temp, str._string);

	return temp;
}

string string::operator+(const char* str)
{
	string temp(*this);
	concat(temp, str);

	return temp;
}

string string::operator*(const size_t count)
{
	string temp(*this);
	repeat(_string, count);
	return temp;
}

bool string::operator==(const string& str)
{
	return compare(str._string);
}

bool string::operator==(const char* str)
{
	return compare(str);
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

size_t string::length(const char* str) const
{
	size_t size = 0;

	while (str[size]) size++;

	return size;
}

void string::copy(const char* source)
{
	if (_string == source || !source) return;

	_len = length(source);
	_capacity = _len * ascending_factor;

	delete[] _string;
	_string = new char[_capacity];

	for (size_t i = 0; i < _len; i++)
	{
		_string[i] = source[i];
	}

	_string[_len] = '\0';
}

void string::concat(string& dest, const char* source) const
{
	size_t len = dest._len + length(source);
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

void string::repeat(const char* source, const short count)
{
	size_t len = length(source);
	_len = len * count;
	_capacity = _len * ascending_factor;

	char* str = new char[_capacity];

	for (size_t i = 0; i < _len; i++)
	{
		_string[i] = source[i % len];
	}

	_string[_len] = '\0';
}

bool string::compare(const char* str) const
{
	if (_len != length(str)) return 0;

	for (size_t i = 0; i < _len; i++)
	{
		if (_string[i] != str[i]) return 0;
	}
	return 1;
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

size_t string::GetLen() { return _len; }

string::~string()
{
	delete[] _string;
}



