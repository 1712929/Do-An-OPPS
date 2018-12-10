#include"string.h"

void main()
{
	// MyString()
	MyString str1;
	cout << "Cin:";
	cin >> str1;
	cout << "Cout:";
	cout << str1 << endl;                 // Empty string

	// MyString(const MyString& str);
	MyString temp = "This is class my string";
	MyString str2(temp);
	cout << str2 << endl;                 // This is class my string

	// MyString(const MyString& str, size_t pos, size_t len);
	MyString str3(temp, 14, 9);
	cout << str3 << endl;                 // my string

	// MyString(const char* s);
	char s4[] = "This is class my string";
	MyString str4(s4);
	cout << str4 << endl;                 // This is class my string

	// MyString(const char*s, size_t n);
	MyString str5(s4, 7);
	cout << str5 << endl;				  // This is

	// MyString(size_t n, char c);
	MyString str6(5, 'c');
	cout << str6 << endl;                 // ccccc

	// operator = ;
	MyString str7 = str2;
	cout << str7 << endl;                 // This is class my string
	MyString str8 = "C plus plu";
	MyString str9 = "s";
	cout << str8 << str9 << endl;

	system("pause");
}