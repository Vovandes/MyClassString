#pragma once

#include <iostream>

namespace mcs {
	class MyClassString {
	public:
		MyClassString() : lenght{ 0 }, string{ nullptr }{};
		MyClassString(const char* newString);

		MyClassString(const MyClassString& other) noexcept;
		MyClassString(MyClassString&& other) noexcept;

		~MyClassString();

		void ClearString();

		MyClassString& operator = (const MyClassString& other);
		MyClassString& operator = (const char* temp_string);

		MyClassString operator + (const MyClassString& other) const;
		MyClassString operator + (const char* temp_string) const;

		MyClassString& operator += (const MyClassString& other);
		MyClassString& operator += (const char* temp_string);

		char& operator[](int index);

		unsigned MySizeFunctions(const char* string) const;

		unsigned GetSizeString() const;

		friend std::ostream& operator<<(std::ostream& out, const MyClassString& s);
		friend std::istream& operator>>(std::istream& in, MyClassString& s);


	private:
		char* string;
		unsigned lenght;
		void DeleteString();
	};
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ctor #1
inline mcs::MyClassString::MyClassString(const char* newString) {
	this->lenght = mcs::MyClassString::MySizeFunctions(newString);
	auto size = this->lenght;
	this->string = new char[size + 1]{ '\0' };
	for (unsigned i = 0; i < size; ++i) {
		this->string[i] = newString[i];
	}
}

// Copy Constructor
inline mcs::MyClassString::MyClassString(const MyClassString& other) noexcept {
	this->lenght = mcs::MyClassString::MySizeFunctions(other.string);
	auto size = this->lenght;
	this->string = new char[size + 1]{ '\0' };
	for (unsigned i = 0; i < size; ++i) {
		this->string[i] = other.string[i];
	}
}

// Move Constructor
inline mcs::MyClassString::MyClassString(MyClassString&& other) noexcept {
	// std::cout << "Move constructor" << std::endl;
	this->lenght = other.lenght;
	this->string = other.string;
	other.string = nullptr;
}

// Destructor
inline mcs::MyClassString::~MyClassString() {
	mcs::MyClassString::DeleteString();
}

// Clear String
inline void mcs::MyClassString::ClearString() {
	mcs::MyClassString::DeleteString();
}

// Reload operator = for class
inline mcs::MyClassString& mcs::MyClassString::operator=(const MyClassString& other) {
	if (this->string != nullptr) {
		this->DeleteString();
	}
	this->lenght = other.lenght;
	this->string = new char[this->lenght + 1]{ '\0' };
	for (unsigned i = 0; i < this->lenght; ++i) {
		this->string[i] = other.string[i];
	}

	return *this;
}

// Reload operator = for const char*
inline mcs::MyClassString& mcs::MyClassString::operator=(const char* temp_string) {
	MyClassString temp(temp_string);

	return *this = temp;
}

// Reload operator + for class
inline mcs::MyClassString mcs::MyClassString::operator+(const MyClassString& other) const {
	MyClassString temp;
	temp.lenght = this->lenght + other.lenght;
	temp.string = new char[temp.lenght + 1]{ '\0' };

	for (unsigned i = 0; i < temp.lenght; ++i) {
		i < this->lenght ? temp.string[i] = this->string[i] : temp.string[i] = other.string[i - this->lenght];
	}

	return temp;
}

// Reload operator + for const char*
inline mcs::MyClassString mcs::MyClassString::operator+(const char* temp_string) const {
	MyClassString temp(temp_string);

	return temp = *this + temp;
}

// Reload operator += for class
inline mcs::MyClassString& mcs::MyClassString::operator+=(const MyClassString& other) {
	return *this = *this + other;
}

// Reload operator += for const char*
inline mcs::MyClassString& mcs::MyClassString::operator+=(const char* temp_string) {
	MyClassString temp(temp_string);
	return *this = *this + temp;
}

// Reload operator []
inline char& mcs::MyClassString::operator[](int index) {
	return this->string[index];
}

// strlen ->
inline unsigned mcs::MyClassString::MySizeFunctions(const char* string_temp) const {
	unsigned count{ 0 };
	for (unsigned i = 0; string_temp[i] != '\0'; ++i, ++count);

	return count;
}

// Get Size String
inline unsigned mcs::MyClassString::GetSizeString() const {
	return this->lenght;
}

// Delete String
inline void mcs::MyClassString::DeleteString() {
	if (this->string != nullptr) {
		delete this->string;
		this->lenght = 0;
		this->string = nullptr;
	}
}

// Reload  <<
std::ostream& mcs::operator<<(std::ostream& out, const MyClassString& s) {
	return out << s.string;
}

// Reload  >>
std::istream& mcs::operator>>(std::istream& in, MyClassString& s) {
	char buff[255]{};
	in >> buff;
	auto size = s.MySizeFunctions(buff);
	s.ClearString();
	s.string = new char[size + 1]{ 0 };
	for (unsigned i = 0; i < size; ++i) {
		s.string[i] = buff[i];
	}
	s.lenght = s.MySizeFunctions(s.string);

	return in;
}
