#include "myClassString.hpp"

mcs::MyClassString CreateString(const char* buffer) {
	mcs::MyClassString temp(buffer);
	return temp;
}

int main() {
	setlocale(LC_ALL, "");

	mcs::MyClassString str = "Hello";
	mcs::MyClassString str2("World");

	mcs::MyClassString str3 = "QRT";

	//std::cin >> str3;

	//str += "KO";

	//str += str3;

	str3.EmplaceBack('w');

	std::cout << str3 << std::endl;

	/*std::cout << str << std::endl;

	std::cout << str.GetSizeString() << std::endl;

	std::cout << str[7] << std::endl;

	str.ClearString();

	std::cout << str.GetSizeString() << std::endl;*/



	return 0;
}