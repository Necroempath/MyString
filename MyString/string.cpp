#include "string.h"
#define ascending_factor 2.0f
#define descending_factor .5f

string::string() { Default(); }

string::string(const char* str)
{
	if (!str)
	{
		Default();
		return;
	}

	copy(*this, str);
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

	copy(*this, other._string);
}

string::string(string&& other) noexcept { Init(other); other._string = nullptr; }

string& string::operator=(const string& other)
{
	copy(*this, other._string);
	return *this;
}

string& string::operator=(string&& other) noexcept
{
	if (this == &other || !other._string) return *this;

	Init(other);

	other._string = nullptr;
	return *this;
}

string& string::operator=(const char* str)
{
	copy(*this, str);
	return *this;
}

string string::operator+(const string& str) const
{
	string temp(*this);
	concat(temp, str._string);
	
	return temp;
}

string string::operator+(const char* str) const
{
	string temp(*this);
	concat(temp, str);

	return temp;
}

string& string::operator+=(const string& str)
{
	*this = *this + str;
	return *this;
}

string& string::operator+=(const char* str)
{
	*this = *this + str;
	return *this;
}

string string::operator*(const size_t count) const
{
	string temp(*this);
	repeat(temp, _string, count);
	return temp;
}

string& string::operator*=(const size_t count)
{
	repeat(*this, _string, count);
	return *this;
}

bool string::operator==(const string& str) const
{
	return compare(str._string);
}

bool string::operator==(const char* str) const
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
	char* buffer = new char[100];
	is >> buffer;
	str = string(buffer);
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

void string::copy(string& dest, const char* source) const
{
	if (_string == source || !source) return;

	dest._len = length(source);
	dest._capacity = _len * ascending_factor;
	dest._string = new char[_capacity];

	for (size_t i = 0; i < _len; i++)
	{
		dest._string[i] = source[i];
	}

	dest._string[_len] = '\0';
}

void string::concat(string& dest, const char* source) const
{
	size_t source_len = dest._len + length(source);
	dest._len += source_len;
	dest._capacity = dest._len * ascending_factor;

	dest._string = new char[dest._capacity];
	
	for (size_t i = 0; i < dest._len; i++)
	{
		dest._string[i] = dest._string[i];
	}

	for (size_t i = dest._len, j = 0; i < source_len; i++, j++)
	{
		dest._string[i] = source[j];
	}
	dest._string[source_len] = '\0';
}

void string::repeat(string& dest, const char* source, const short count) const
{
	if (count < 0) return;
	if (count == 0) { dest.Default(); return; }

	size_t source_len = length(source);

	dest._len = source_len * count;
	dest._capacity = _len * ascending_factor;
	dest._string = new char[dest._capacity];

	for (size_t i = 0; i < dest._len; i++)
	{
		dest._string[i] = source[i % source_len];
	}

	dest._string[dest._len] = '\0';
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

long string::find(const char* str) const
{
	size_t str_len = length(str);

	for (size_t i = 0, j = 0; i < _len - (str_len - j - 1); i++)
	{
		if (_string[i] == str[j])
		{
			if (++j == str_len) return i - j + 1;
		}
		else if (j > 0) { j = 0; i--; }
	}

	return -1;
}

void string::remove(const size_t index, const size_t len)
{
	for (size_t i = index; i < _len - len; i++)
	{
		_string[i] = _string[i + len];
	}
	_len -= len;
	_string[_len] = '\0';

	if (_capacity * descending_factor >= _len) ResizeString(descending_factor);
}

void string::ResizeString(const float factor)
{
	_capacity *= factor;

	char* temp = new char[_capacity];

	for (size_t i = 0; i < _len; i++)
	{
		temp[i] = _string[i];
	}
	temp[_len] = '\0';

	delete[] _string;
	_string = temp;
}

size_t string::GetLen() { return _len; }

long string::Find(const char value) const
{
	for (size_t i = 0; i < _len; i++)
	{
		if (_string[i] == value) return i;
	}

	return -1;
}

long string::Find(const char* str) const
{
	return (find(str));
}

long string::Find(const string& str) const
{
	return (find(str._string));
}

bool string::Remove(const char value)
{
	size_t index = Find(value);
	if (index < 0) return 0;

	remove(index, 1);
	return 1;
}

bool string::Remove(const char* str)
{
	size_t index = Find(str);

	if (index < 0) return 0;

	remove(index, length(str));
	return 1;
}

bool string::Remove(const string& str)
{
	size_t index = Find(str);

	if (index < 0) return 0;

	remove(index, str._len);
	return 1;
}

string::~string()
{
	delete[] _string;
}



