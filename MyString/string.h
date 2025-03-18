#pragma once
#include <iostream>
class string
{
	char* _string;
	size_t _len;
	size_t _capacity;

	void Default();
	void Init(const string& str);
	size_t length(const char* str) const;
	void copy(string& dest, const char* source) const;
	void concat(string& dest, const char* source) const;
	void repeat(string& dest, const char* source, const short count) const;
	bool compare(const char* str) const;
	long find(const char* str) const;
	void remove(const size_t index, const size_t len);
	void ResizeString(const float factor);

public:
	string();

	explicit string(const char* str);

	explicit string(const size_t len);

	string(const string& other);

	string(string&& other) noexcept;

	string& operator=(const string& other);

	string& operator=(string&& other) noexcept;

	string& operator=(const char* str);

	string operator+(const string& str) const;

	string operator+(const char* str) const;

	string& operator+=(const string& str);

	string& operator+=(const char* str);

	bool operator==(const string& str) const;

	bool operator==(const char* str) const;

	string operator*(const size_t count) const;

	string& operator*=(const size_t count);

	const char operator[](const size_t index) const;

	char& operator[](size_t index);

	friend std::ostream& operator<<(std::ostream& os, const string& str);

	friend std::istream& operator>>(std::istream& is, string& str);

	size_t GetLen();

	long Find(const char value) const;

	long Find(const char* str) const;

	long Find(const string& str) const;

	bool Remove(const char value);

	bool Remove(const char* str);

	bool Remove(const string& str);

	~string();
};
