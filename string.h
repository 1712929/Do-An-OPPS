#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include<iostream>
#include <iterator>
#include <initializer_list>
#include <cstring>
using namespace std;

class Iterator : public iterator<random_access_iterator_tag, char>
{
	char* p;
public:
	Iterator(char* x) :p(x)
	{}
	Iterator(const Iterator& it) : p(it.p) 
	{}
	Iterator& operator++()
	{
		++p; 
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator tmp(*this);
		operator++(); 
		return tmp; 
	}
	Iterator& operator--() 
	{
		--p;
		return *this; 
	}
	Iterator operator--(int)
	{
		Iterator tmp(*this); 
		operator--(); 
		return tmp; 
	}
	bool operator==(const Iterator& rhs)
	{
		return p == rhs.p; 
	}
	bool operator!=(const Iterator& rhs) 
	{ 
		return p != rhs.p;
	}
	char& operator*()
	{ 
		return *p; 
	}
	const char& operator*() const
	{
		return *p; 
	}
};

class reverseIterator : public Iterator
{
public:
	reverseIterator(char* x) :Iterator(x)
	{}
	reverseIterator(const reverseIterator& it) : Iterator((char*)(&(*it)))
	{}
	Iterator& operator++() 
	{
		Iterator::operator--();
		return *this;
	}
	Iterator operator++(int)
	{ 
		reverseIterator tmp(*this);
		Iterator::operator--();
		return tmp; 
	}
	Iterator& operator--()
	{
		Iterator::operator++();
		return *this; 
	}
	Iterator operator--(int) 
	{
		reverseIterator tmp(*this);
		operator++(); 
		return tmp; 
	}
	bool operator==(const reverseIterator& rhs)
	{ 
		return Iterator::operator*() == *rhs; 
	}
	bool operator!=(const reverseIterator& rhs)
	{
		return Iterator::operator*() != *rhs;
	}
	char& operator*()
	{
		return Iterator::operator*();
	}
	const char& operator*() const
	{
		return Iterator::operator*();
	}

};

class constIterator : public iterator<random_access_iterator_tag, char>
{
	const char* p;
public:
	constIterator(char* x) :p(x) 
	{}
	constIterator(const constIterator& it) : p(it.p)
	{}
	constIterator& operator++() 
	{
		++p;
		return *this; 
	}
	constIterator operator++(int) 
	{
		constIterator tmp(*this);
		operator++(); return tmp; 
	}
	constIterator& operator--() 
	{
		--p; 
		return *this; 
	}
	constIterator operator--(int) 
	{
		constIterator tmp(*this);
		operator--(); return tmp; 
	}
	bool operator==(const constIterator& rhs) 
	{
		return p == rhs.p;
	}
	bool operator!=(const constIterator& rhs) 
	{
		return p != rhs.p; 
	}
	const char& operator*() 
	{
		return *p; 
	}
};
class MyString
{
private:
	char* str;
	size_t maxSize;
	size_t str_capacity;

	char* AllocateNewString(size_t capacity);
	void AllocateString(size_t length);
public:
	static const size_t npos = -1;

	MyString();
	MyString(const MyString& other);
	MyString(const MyString& other, size_t pos, size_t len = npos);
	MyString(const char* other);
	MyString(const char* other, size_t n);
	MyString(size_t n, char c);

	template <class InputIterator>
	MyString(InputIterator first, InputIterator last);

	~MyString();

	MyString& operator =(const MyString&str2);
	MyString& operator =(const char* str2);
	MyString& operator =(char c);


	Iterator begin()
	{
		return Iterator(str);
	}
	const Iterator begin() const 
	{
		return Iterator(str);
	}
	Iterator end() 
	{
		return Iterator(str + maxSize); 
	}
	const Iterator end() const 
	{
		return Iterator(str + maxSize);
	}
	reverseIterator rbegin() 
	{
		return reverseIterator(str + maxSize - 1); 
	}
	const reverseIterator rbegin() const 
	{
		return reverseIterator(str + maxSize - 1); 
	}
	reverseIterator rend() 
	{
		return reverseIterator(str - 1);
	}
	const reverseIterator rend() const 
	{
		return reverseIterator(str - 1); 
	}

	size_t size() const;
	size_t length() const;
	size_t max_size()const;
	void resize(size_t n);
	void resize(size_t n, char c);
	size_t capacity()const;
	void reserve(size_t n = 0);
	void clear();
	bool empty()const;
	void shrink_to_fit();

	char& operator[] (size_t pos);
	const char& operator[] (size_t pos) const;
	char& at(size_t pos);
	const char& at(size_t pos) const;
	char& back();
	const char& back() const;
	char& front();
	const char& front() const;

	MyString& operator+= (const MyString& rhs);
	MyString& operator+= (const char* rhs);
	MyString& operator+= (char c);

	MyString& append(const MyString& str);
	MyString& append(const MyString& str, size_t subpos, size_t sublen);
	MyString& append(const char* str);
	MyString& append(const char* str, size_t n);
	MyString& append(size_t n, char c);
	MyString& append(Iterator first, Iterator last);

	void push_back(char c);

	MyString& assign(const MyString& str);
	MyString& assign(const MyString& str, size_t subpos, size_t sublen);
	MyString& assign(const char* str);
	MyString& assign(const char* str, size_t n);
	MyString& assign(size_t n, char c);
	MyString& assign(Iterator first, Iterator last);

	MyString& insert(size_t pos, const MyString& str);
	MyString& insert(size_t pos, const MyString& str, size_t subpos, size_t sublen);
	MyString& insert(size_t pos, const char* str);
	MyString& insert(size_t pos, const char* str, size_t n);
	MyString& insert(size_t pos, size_t n, char c);

	MyString& erase(size_t pos = 0, size_t len = npos);
	Iterator erase(Iterator p);
	Iterator erase(Iterator first, Iterator last);

	MyString& replace(size_t pos, size_t len, const MyString& str);
	MyString& replace(size_t pos, size_t len, const MyString& str, size_t subpos, size_t sublen);
	MyString& replace(size_t pos, size_t len, const char* str);
	MyString& replace(size_t pos, size_t len, const char* str, size_t n);
	MyString& replace(size_t pos, size_t len, size_t n, char c);

	MyString& Replace(Iterator i1, Iterator i2, const MyString& str);
	MyString& Replace(Iterator i1, Iterator i2, const char* s);
	MyString& Replace(Iterator i1, Iterator i2, const char* s, size_t n);
	MyString& Replace(Iterator i1, Iterator i2, size_t n, char c);
	MyString& Replace(Iterator i1, Iterator i2, Iterator first, Iterator last);

	void swap(MyString &s);

	void popback();

	const char*c_str()const;

	const char*data()const;

	size_t copy(char* s, size_t len, size_t pos = 0) const;

	size_t find(const MyString& str, size_t pos = 0) const;
	size_t find(const char* s, size_t pos = 0) const;
	size_t find(const char* s, size_t pos, size_t n) const;
	size_t find(char c, size_t pos = 0) const;

	size_t rfind(const MyString& str, size_t pos = npos) const;
	size_t rfind(const char* s, size_t pos = npos) const;
	size_t rfind(const char* s, size_t pos, size_t n) const;
	size_t rfind(char c, size_t pos = npos) const;

	size_t find_first_of(const MyString& str, size_t pos = 0) const;
	size_t find_first_of(const char* s, size_t pos = 0) const;
	size_t find_first_of(const char* s, size_t pos, size_t n) const;
	size_t find_first_of(char c, size_t pos = 0) const;

	size_t find_last_of(const MyString& str, size_t pos = npos) const;
	size_t find_last_of(const char* s, size_t pos = npos) const;
	size_t find_last_of(const char* s, size_t pos, size_t n) const;
	size_t find_last_of(char c, size_t pos = npos) const;

	size_t find_first_not_of(const MyString& str, size_t pos = 0) const;
	size_t find_first_not_of(const char* s, size_t pos = 0) const;
	size_t find_first_not_of(const char* s, size_t pos, size_t n) const;
	size_t find_first_not_of(char c, size_t pos = 0) const;

	size_t find_last_not_of(const MyString& str, size_t pos = npos) const;
	size_t find_last_not_of(const char* s, size_t pos = npos) const;
	size_t find_last_not_of(const char* s, size_t pos, size_t n) const;
	size_t find_last_not_of(char c, size_t pos = npos) const;

	MyString substr(size_t pos = 0, size_t len = npos) const;

	int compare(const MyString& str) const;
	int compare(size_t pos, size_t len, const MyString& str) const;
	int compare(size_t pos, size_t len, const MyString& str, size_t subpos, size_t sublen) const;
	int compare(const char* s) const;
	int compare(size_t pos, size_t len, const char* s) const;
	int compare(size_t pos, size_t len, const char* s, size_t n) const;

	MyString operator+ (const MyString& rhs);
	MyString operator+ (const char* rhs);
	MyString operator+ (char c);

	friend MyString operator+ (const MyString& lhs, const MyString& rhs);
	friend MyString operator+ (const MyString& lhs, const char* rhs);
	friend MyString operator+ (const char* lhs, const MyString& rhs);
	friend MyString operator+ (char c, const MyString& rhs);
	friend MyString operator+ (const MyString& lhs, char c);

	friend bool operator== (const MyString& lhs, const MyString& rhs);
	friend bool operator== (const char*   lhs, const MyString& rhs);
	friend bool operator== (const MyString& lhs, const char*   rhs);

	friend bool operator!= (const MyString& lhs, const MyString& rhs);
	friend bool operator!= (const char*   lhs, const MyString& rhs);
	friend bool operator!= (const MyString& lhs, const char*   rhs);

	friend bool operator<  (const MyString& lhs, const MyString& rhs);
	friend bool operator<  (const char*   lhs, const MyString& rhs);
	friend bool operator<  (const MyString& lhs, const char*   rhs);

	friend bool operator<= (const MyString& lhs, const MyString& rhs);
	friend bool operator<= (const char*   lhs, const MyString& rhs);
	friend bool operator<= (const MyString& lhs, const char*   rhs);

	friend bool operator>  (const MyString& lhs, const MyString& rhs);
	friend bool operator>  (const char*   lhs, const MyString& rhs);
	friend bool operator>  (const MyString& lhs, const char*   rhs);

	friend bool operator>= (const MyString& lhs, const MyString& rhs);
	friend bool operator>= (const char*   lhs, const MyString& rhs);
	friend bool operator>= (const MyString& lhs, const char*   rhs);

	friend void swap(MyString& x, MyString& y);

	friend istream& operator>> (istream& is, MyString& str);
	friend ostream& operator<< (ostream& os, const MyString& str);
	friend istream& getline(istream& is, MyString& str, char delim);
	friend istream& getline(istream& is, MyString& str);
};
#endif