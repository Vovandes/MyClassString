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

		bool operator == (const MyClassString& other);
		bool operator != (const MyClassString& other);

		char& operator[](int index);

		unsigned MySizeFunctions(const char* string) const;

		unsigned GetSizeString() const;

		friend std::ostream& operator<<(std::ostream& out, const MyClassString& s);
		friend std::istream& operator>>(std::istream& in, MyClassString& s);

		void EmplaceBack(const char ch);
		MyClassString& EmplaceBackString(const char* str);

	private:
		char* string;
		unsigned lenght;
		void DeleteString();
		void CopyFunctions(const char* temp_string, unsigned size);
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
	this->lenght = MySizeFunctions(newString);
	this->string = new char[this->lenght + 1]{ '\0' };
	CopyFunctions(newString, this->lenght);
}

// Copy Constructor
inline mcs::MyClassString::MyClassString(const MyClassString& other) noexcept {
	this->lenght = MySizeFunctions(other.string);
	this->string = new char[this->lenght + 1]{ '\0' };
	CopyFunctions(other.string, this->lenght);
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
	CopyFunctions(other.string, this->lenght);

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

	return temp = this->operator+(temp);
}

// Reload operator += for class
inline mcs::MyClassString& mcs::MyClassString::operator+=(const MyClassString& other) {
	return this->operator=(*this + other);
}

// Reload operator += for const char*
inline mcs::MyClassString& mcs::MyClassString::operator+=(const char* temp_string) {
	MyClassString temp(temp_string);
	return this->operator=(*this + temp);
}

// Reload operator ==
inline bool mcs::MyClassString::operator==(const MyClassString& other) {
	if (this->lenght == other.lenght) {
		return false;
	}
	for (unsigned i = 0; i < this->lenght; ++i) {
		if (this->string[i] != other.string[i]) {
			return false;
		}
	}

	return true;
}

// Reload operator !=
inline bool mcs::MyClassString::operator!=(const MyClassString& other) {
	return !(this->operator==(other));
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

// Set const char in back
inline void mcs::MyClassString::EmplaceBack(const char ch) {
	auto size = this->lenght + 1;
	auto temp = new char[size + 1]{ '\0' };
	if (this->string != nullptr) {
		for (unsigned i = 0; i < this->lenght; ++i) {
			temp[i] = this->string[i];
		}
		this->DeleteString();
	}
	temp[size - 1] = ch;
	this->lenght = size;
	this->string = new char[size + 1]{ '\0' };
	CopyFunctions(temp, size);

	delete[] temp;
	temp = nullptr;
}

// Set const char* in back
inline mcs::MyClassString& mcs::MyClassString::EmplaceBackString(const char* str) {
	return operator+=(str);
}

// Delete String
inline void mcs::MyClassString::DeleteString() {
	if (this->string != nullptr) {
		delete this->string;
		this->lenght = 0;
		this->string = nullptr;
	}
}

// Copy element array
inline void mcs::MyClassString::CopyFunctions(const char* temp_string, unsigned size) {
	for (unsigned i = 0; i < size; ++i) {
		this->string[i] = temp_string[i];
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
