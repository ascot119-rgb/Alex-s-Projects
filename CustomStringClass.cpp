// Assignment 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
#include <assert.h>

class String {
public:
	String(const char* s);
	~String();
	String(const String& copiedString);
	String& operator=(const String& copiedString);
	friend std::ostream& operator<<(std::ostream& out, const String& StringData);
	char& operator[](int index);
	String operator+(const String&) const;
	const char& operator[](int index) const;
	void push_back(const char inputchar);
private:
	char* characters;
	int len;
	int strCap;
};

String::String(const char* s) {
	len = strlen(s);
	strCap = len + 1;
	characters = new char[strCap];
	strcpy_s(characters, strCap, s);
}

String::~String() {
	delete[] characters;
	std::cout << "Destroyed!" << std::endl;
}

String::String(const String& copiedString) {
	len = copiedString.len;
	strCap = copiedString.strCap;
	characters = new char[strCap];
	strcpy_s(characters, strCap, copiedString.characters);
}

char& String::operator[](int index) {
	return characters[index];
}

/*String String::operator+(const String& addedString) const
{
	int newlen = len + strlen(addedString.characters) + 1;
	char* input = new char[newlen];
	strcpy_s(input, newlen, characters);
	strcat_s(input, newlen, addedString.characters);
	String output(input);
	delete[] input;
	return output;
} */

const char& String::operator[](int index) const {
	return characters[index];
}
void String::push_back(const char inputchar)
{
	len++;
	strCap = len + 1;
	char* newcharacters = new char[len + 1];
	strcpy_s(newcharacters, strCap, characters);
	newcharacters[len - 1] = inputchar;
	newcharacters[len] = '\0';
	delete[] characters;
	characters = newcharacters;
}

String& String::operator=(const String& copiedString)
{
	std::cout << "Assignment Op Called" << std::endl;
	if (this != &copiedString)
	{
		delete[] characters;
		len = copiedString.len;
		strCap = copiedString.strCap;
		characters = new char[strCap];
		strcpy_s(characters, strCap, copiedString.characters);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const String& StringData)
{
	out << StringData.characters;
	return out;
}

int main()
{
	String a("Hello");
	std::cout << "T1:" << a << std::endl;

	String b = a;
	b[0] = 'Y';
	std::cout << "T2a:" << a << std::endl;
	std::cout << "T2b:" << b << std::endl;

	String c("abc");
	c = a; // c becomes " Hello "
	a[1] = 'a'; // mutate original a -> " Hallo "
	std::cout << "T3a:" << a << std::endl; // T3a : Hallo
	std::cout << "T3b:" << c << std::endl;

	a = a;
	std::cout << "T4:" << a << std::endl;


	/*String d = b + String(" World ");
	std::cout << "T5:" << d << std::endl;

	d.push_back('!');
	std::cout << " T6 : " << d << std::endl; */
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
