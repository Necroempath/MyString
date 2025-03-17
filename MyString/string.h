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
	void copy(const char* source);
	void concat(string& dest, const char* source) const;
	bool compare(const char* str) const;
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

	string operator+(const string& str);

	string operator+(const char* str);

	bool operator==(const string& str);

	bool operator==(const char* str);

	const char operator[](const size_t index) const;

	char& operator[](size_t index);

	friend std::ostream& operator<<(std::ostream& os, const string& str);

	friend std::istream& operator>>(std::istream& is, string& str);

	size_t GetLen();

	~string();
};
