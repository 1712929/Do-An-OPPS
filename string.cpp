#include "string.h"

//--------------------Member functions--------------------
char* MyString::AllocateNewString(size_t capacity)
{
	char * string = new char[capacity + 2];
	++string;
	return string;
}

void MyString::AllocateString(size_t length)
{
	if (length == 0)
	{
		maxSize = 0;
		str_capacity = 0;

		str = nullptr;
	}
	else
	{
		maxSize = length;
		str_capacity = 2 * maxSize;

		str = new char[str_capacity + 2];
		++str;
	}
}
MyString::MyString() :str(nullptr), maxSize(0), str_capacity(15)
{
	str = new char[str_capacity];
	memset(str, 0, str_capacity);
}
MyString::MyString(const MyString& other)
{
	str = new char[strlen(other.str) + 1];
	strcpy(this->str, other.str);
}
MyString::MyString(const char* other)
{
	if (other == NULL||strlen(other)==0)
	{
		MyString();
		return;
	}
	else
	{
		maxSize = strlen(other);
		str_capacity = strlen(other);
		str = new char[maxSize + 1];
		strcpy(str, other);
	}
}
MyString::MyString(const MyString& other, size_t pos, size_t len)
{
	if (this != &other)
	{
		maxSize = (len != -1) ? len : (other.length() - pos);
		str_capacity = other.capacity();
		str = new char[str_capacity];
		memset(str, 0, str_capacity);
		strncpy(str, other.str + pos, maxSize);
	}
}
MyString::MyString(const char* other, size_t n) :maxSize(n), str_capacity(15)
{
	if (maxSize > 15)
		str_capacity += maxSize;
	if (n == npos)
		maxSize = strlen(other);
	str = new char[str_capacity];
	memset(str, 0, str_capacity);
	if (str)
	{
		memcpy(str, other, maxSize);
	}
}
MyString::MyString(size_t n, char c)
{
	maxSize = n;
	str_capacity = n;
	str = new char[maxSize + 1];
	memset(str, c, n);
	str[maxSize] = '\0';
}

template <class InputIterator>
MyString::MyString(InputIterator first, InputIterator last)
{
	size_t length = 0;
	for (auto it = first; first != last; it++)
	{
		++length;
	}

	if (length == 0)
	{
		MyString();
		return;
	}

	AllocateString(length);

	size_t i = 0;
	for (auto it = first; first != last; ++it, ++i)
	{
		str[i] = *it;
	}
}
MyString::~MyString()
{
	if (str)
	{
		delete[]str;
		str = NULL;
	}
	maxSize = str_capacity = 0;
}

MyString& MyString::operator =(const MyString& str2)
{
	clear();
	maxSize = str2.maxSize;
	str = new char[maxSize + 1];
	strcpy(str, str2.str);
	str[maxSize] = '\0';
	return *this;
}
MyString& MyString::operator=(const char* str2)
{
	clear();
	maxSize = strlen(str2);
	str = new char[maxSize + 1];
	strcpy(str, str2);
	str[maxSize] = '\0';
	return *this;
}
MyString& MyString::operator=(char c)
{
	clear();
	maxSize = 1;
	memset(str, 0, str_capacity);
	str[0] = c;
	return *this;
}

//--------------------Iterators:--------------------

//string.h

//--------------------Capacity:--------------------
size_t MyString::size() const
{
	return maxSize;
}
size_t MyString::length()const
{
	return maxSize;
}
size_t MyString::max_size()const
{
	return (((npos - (sizeof(size_t)+sizeof(size_t)+sizeof(long))) / sizeof(char)) - 1) / 4 - 1;
}
void MyString::resize(size_t n)
{
	resize(n, '\0');
}
void MyString::resize(size_t n, char c)
{
	if (n == npos || n > max_size())
	{
		throw "length error!";
	}
	
	if (n < maxSize)
	{
		str[n] = '\0';
	}
	else
	{
		if (n>str_capacity)
		{
			reserve(n + 1);
		}
		size_t i = maxSize;
		while (i<=n)
		{
			str[i] = c;
			i++;
		}
		str[n] = '\0';
	}
	maxSize = n;
}
size_t MyString::capacity()const
{
	return str_capacity;
}
void MyString::reserve(size_t n)
{
	if (n > 0 && n < max_size())
	{
		if (n< maxSize)
		{
			n = maxSize;
		}

		char * newString = AllocateNewString(n);
		for (size_t i = 0; i < maxSize; ++i)
		{
			newString[i] = str[i];
		}

		str_capacity = n;
		clear();
		str = newString;
	}
}
void MyString::clear()
{
	delete []str;
	str = NULL;
	maxSize = 0;
	str_capacity = 0;
}
bool MyString::empty()const
{
	return maxSize == 0;
}
void MyString::shrink_to_fit()
{
	str_capacity = maxSize;
	char *t = new char[maxSize + 1];
	memmove(t, str, maxSize);
	delete[]t;
	str = t;
}

//--------------------Element access:--------------------
char& MyString::operator[](size_t pos)
{
	return str[pos];
}
const char& MyString::operator[](size_t pos) const
{
	return str[pos];
}
char& MyString::at(size_t pos)
{
	return str[pos];
}
const char &MyString::at(size_t pos) const
{
	return str[pos];
}
char& MyString::back()
{
	return str[maxSize - 1];
}
const char &MyString::back() const
{
	return str[maxSize - 1];
}
char& MyString::front()
{
	return str[0];
}
const char &MyString::front() const
{
	return str[0];
}

//--------------------Modifiers:--------------------
MyString& MyString::operator+=(const char* rhs)
{
	size_t strLength = strlen(rhs);

	size_t newLength = maxSize + strLength;

	if (newLength > max_size())
	{
		return *this;
	}

	if (newLength <= str_capacity)
	{
		for (size_t i = maxSize; i < newLength; ++i)
		{
			str[i] = str[i - maxSize];
		}
		maxSize = newLength;
	}
	else
	{
		size_t priviousLength = maxSize;
		resize(newLength);

		for (size_t i = priviousLength; i < newLength; ++i)
		{
			str[i] = str[i - priviousLength];
		}
	}
	return *this;
}
MyString& MyString::operator+=(const MyString& rhs)
{
	return *this += rhs.str;
}
MyString& MyString::operator+=(char c)
{
	if (maxSize + 1 <= str_capacity)
	{
		str[maxSize] = c;
		maxSize++;
	}
	else
	{
		size_t priviousLength = maxSize;
		resize(maxSize + 1);

		str[priviousLength] = c;
	}
	return *this;
}
MyString& MyString::append(const MyString& s)
{
	return *this += s;
}
MyString& MyString::append(const MyString& s, size_t subpos, size_t sublen)
{
	return *this += MyString(s, subpos, sublen);
}
MyString& MyString::append(const char* s)
{
	return *this += s;
}
MyString& MyString::append(const char* s, size_t n)
{
	return *this += MyString(s, n);
}
MyString& MyString::append(size_t n, char c)
{
	return *this += MyString(n, c);
}
MyString& MyString::append(Iterator first, Iterator last)
{
	return *this += MyString(first, last);
}
void MyString::push_back(char c)
{
	*this += c;
}
MyString& MyString::assign(const MyString& s)
{
	return *this = s;
}
MyString& MyString::assign(const MyString& s, size_t subpos, size_t sublen)
{
	return *this = MyString(s, subpos, sublen);
}
MyString& MyString::assign(const char* s)
{
	return *this = s;
}
MyString& MyString::assign(const char* s, size_t n)
{
	return *this = MyString(s, n);
}
MyString& MyString::assign(size_t n, char c)
{
	return *this = MyString(n, c);
}
MyString& MyString::assign(Iterator first, Iterator last)
{
	return *this = MyString(first, last);
}
MyString& MyString::insert(size_t pos, const MyString& s)
{
	if (pos >= maxSize)
	{
		throw "length error!";
	}
	size_t newLength = maxSize + s.maxSize;
	MyString endStringPart(*this, pos, maxSize - pos);
	resize(newLength);
	for (size_t i = pos; i < s.maxSize + pos; ++i)
	{
		str[i] = s.str[i - pos];
	}

	for (size_t i = s.maxSize + pos; i < s.maxSize + pos + endStringPart.maxSize; ++i)
	{
		str[i] = endStringPart.str[i - pos - s.maxSize];
	}

	return *this;
}
MyString& MyString::insert(size_t pos, const MyString& str, size_t subpos, size_t sublen)
{
	return insert(pos, MyString(str, subpos, sublen));
}
MyString& MyString::insert(size_t pos, const char* src)
{
	return insert(pos, MyString(src));
}
MyString& MyString::insert(size_t pos, const char* src, size_t n)
{
	return insert(pos, MyString(src, n));
}
MyString& MyString::insert(size_t pos, size_t n, char c)
{
	return insert(pos, MyString(n, c));
}

MyString& MyString::erase(size_t pos, size_t len)
{
	if (pos > maxSize || len == 0)
	{
		return *this;
	}
	const size_t n = pos + len;
	if (n >= maxSize || n < pos)
	{
		str[pos] = '\0';
		maxSize = pos;
		return *this;
	}
	size_t left = maxSize - n + 1;
	memmove(str + pos, str + n, left);
	maxSize = maxSize - len;
	return *this;
}

Iterator MyString::erase(Iterator p)
{
	size_t pos = 0;
	for (Iterator i = this->begin(); i != p; i++) 
		pos++; 
	erase(pos, 1);
	return Iterator(p);
}

Iterator MyString::erase(Iterator first, Iterator last)
{
	size_t len = 0;
	size_t pos = 0;
	for (auto it = begin(); it != first; it++)  
		pos++; 
	for (auto it = first; it != last; ++it)
		len++; 
	erase(pos, len);
	return Iterator(first);
}

MyString& MyString::replace(size_t pos, size_t len, const MyString& str)
{
	erase(pos, len);
	insert(pos, str);
	return *this;
}
MyString& MyString::replace(size_t pos, size_t len, const MyString& str, size_t subpos, size_t sublen)
{
	MyString replaceStr(str, subpos, sublen);
	erase(pos, len);
	insert(pos, replaceStr);
	return *this;
}
MyString& MyString::replace(size_t pos, size_t len, const char* str)
{
	erase(pos, len);
	insert(pos, str);
	return *this;
}
MyString& MyString::replace(size_t pos, size_t len, const char* str, size_t n)
{
	MyString temp(str, 0, n);
	return replace(pos, len, temp);
}
MyString& MyString::replace(size_t pos, size_t len, size_t n, char c)
{
	MyString temp(n, c);
	return replace(pos, len, temp);
}
MyString& MyString::Replace(Iterator i1, Iterator i2, const MyString& str)
{
	erase(i1, i2);
	size_t pos = 0;
	for (auto it = begin(); it != i1; it++)
		pos++;
	insert(pos, str);
	return *this;
}
MyString& MyString::Replace(Iterator i1, Iterator i2, const char* s)
{
	MyString temp(s);
	return Replace(i1, i2, temp);
}
MyString& MyString::Replace(Iterator i1, Iterator i2, const char* s, size_t n)
{
	MyString temp(s, n);
	return Replace(i1, i2, temp);
}
MyString& MyString::Replace(Iterator i1, Iterator i2, size_t n, char c)
{
	MyString temp(n, c);
	return Replace(i1, i2, temp);
}
MyString& MyString::Replace(Iterator i1, Iterator i2, Iterator first, Iterator last)
{
	MyString temp(first, last);
	return Replace(i1, i2, temp);
}

void MyString::swap(MyString &s)
{
	MyString t(s);
	s = *this;
	*this = t;
}
void MyString::popback()
{
	if (str == NULL || maxSize == 0)
		return;
	else
	{
		str[maxSize - 1] = '\0';
		maxSize--;
	}
}

//--------------------String operations:--------------------
const char* MyString::c_str()const
{
	return str;
}
const char* MyString::data()const
{
	return str;
}
size_t MyString::copy(char* s, size_t len, size_t pos) const
{
	MyString temp(*this, pos, len);
	memcpy(s, temp.str, temp.length());
	return temp.length();
}
size_t MyString::find(const MyString& scr, size_t pos) const
{
	return find(scr.str, pos);
}
size_t MyString::find(const char* s, size_t pos) const
{
	char* temp;
	if (temp = strstr(str + pos, s))
		return (temp - str);
	else
		return npos;
}
size_t MyString::find(const char* s, size_t pos, size_t n) const
{
	MyString str(s, 0, n);
	return find(str, pos);
}
size_t MyString::find(char c, size_t pos) const
{
	char* temp;
	if (temp = strchr(str + pos, c))
		return (temp - str);
	else
	return npos;
}
size_t MyString::rfind(const MyString& scr, size_t pos) const
{

	size_t temp = find(scr);
	size_t lastPos = npos;
	while (temp < pos)
	{
		lastPos = temp;
		temp = find(scr, temp + 1);
	}
	if (lastPos != npos)
		return lastPos;
	return npos;
}
size_t MyString::rfind(const char* s, size_t pos) const
{
	MyString str(s);
	return this->rfind(str, pos);
}
size_t MyString::rfind(const char* s, size_t pos, size_t n) const
{
	MyString str(s, 0, n);
	return this->rfind(str, pos);
}
size_t MyString::rfind(char c, size_t pos) const
{
	for (size_t i = pos; i >= 0; i--)
	{
		if (str[i] == c)
		{
			return i;
		}
	}
	return npos;
}
size_t MyString::find_first_of(const MyString& str, size_t pos) const
{
	return find_first_of(str.str, pos);
}
size_t MyString::find_first_of(const char* s, size_t pos) const
{
	return find(s, pos);
}
size_t MyString::find_first_of(const char* s, size_t pos, size_t n) const
{
	if (n > strlen(s))
	{
		n = strlen(s);
	}
	char* substr = new char[n + 1];
	for (size_t i = 0; i < n; i++)
	{
		substr[i] = s[i];
	}
	substr[n] = '\0';
	size_t k = find_first_of(substr, pos);
	delete[]substr;
	return k;
}
size_t MyString::find_first_of(char c, size_t pos) const
{
	return find(c, pos);
}
size_t MyString::find_last_of(const MyString& str, size_t pos) const
{
	return find_last_of(str.str, pos);
}
size_t MyString::find_last_of(const char* s, size_t pos) const
{
	return rfind(s, pos);
}
size_t MyString::find_last_of(const char* s, size_t pos, size_t n) const
{
	if (n > strlen(s))
	{
		n = strlen(s);
	}
	char* substr = new char[n + 1];
	for (size_t i = 0; i < n; i++)
	{
		substr[i] = s[i];
	}
	substr[n] = '\0';
	size_t k = find_last_of(substr, pos);
	delete[]substr;
	return k;
}
size_t MyString::find_last_of(char c, size_t pos) const
{
	return rfind(c, pos);
}
size_t MyString::find_first_not_of(const MyString& str, size_t pos) const
{
	return find_first_not_of(str.str, pos);
}
size_t MyString::find_first_not_of(const char* s, size_t pos) const
{
	for (size_t i = 0; i < maxSize; i++)
	{
		if (str[i] != s[0])
		{
			size_t k = 1;
			for (size_t j = 0; j < strlen(s); j++)
			{
				if (str[pos + i + j] == s[j])
				{
					k = 0;
					break;
				}
			}
			if (k)
			{
				return pos + i;
			}
		}
	}
	return npos;
}
size_t MyString::find_first_not_of(const char* s, size_t pos, size_t n) const
{
	if (n > strlen(s))
	{
		n = strlen(s);
	}
	char* substr = new char[n + 1];
	for (size_t i = 0; i < n; i++)
	{
		substr[i] = s[i];
	}
	substr[n] = '\0';
	size_t k = find_first_not_of(substr, pos);
	delete[]substr;
	return k;
}
size_t MyString::find_first_not_of(char c, size_t pos) const
{
	for (size_t i = pos; i < maxSize; i++)
	{
		if (str[i] != c)
		{
			return pos + i;
		}
	}
	return npos;
}
size_t MyString::find_last_not_of(const MyString& str, size_t pos) const
{
	return find_last_not_of(str.str, pos);
}
size_t MyString::find_last_not_of(const char* s, size_t pos) const
{
	for (size_t i = 0; i < pos; i++)
	{
		if (str[pos - i] != s[strlen(s) - 1])
		{
			size_t k = 1;
			for (size_t j = 0; j <strlen(s); j++)
			{
				if (str[pos - i - j] == s[strlen(s) - j - 1])
				{
					k = 0;
					break;
				}
			}
			if (k)
			{
				return pos + i;
			}
		}
	}
	return npos;
}
size_t MyString::find_last_not_of(const char* s, size_t pos, size_t n) const
{
	if (n > strlen(s))
	{
		n = strlen(s);
	}
	char* substr = new char[n + 1];
	for (size_t i = 0; i < n; i++)
	{
		substr[i] = s[i];
	}
	substr[n] = '\0';
	size_t k = find_last_not_of(substr, pos);
	delete[]substr;
	return k;
}
size_t MyString::find_last_not_of(char c, size_t pos) const
{
	for (size_t i = pos; i >= 0; i--)
	{
		if (str[i] != c)
		{
			return i;
		}
	}
	return npos;
}
MyString MyString::substr(size_t pos, size_t len) const
{
	return MyString(*this, pos, len);
}
int MyString::compare(const MyString& str) const
{
	return compare(0, str.maxSize, str.str);
}
int MyString::compare(size_t pos, size_t len, const MyString& str) const
{
	return compare(pos, len, str.str);
}
int MyString::compare(size_t pos, size_t len, const MyString& str, size_t subpos, size_t sublen) const
{
	if (subpos + sublen>str.maxSize)
	{
		sublen = str.maxSize - subpos;
	}
	char* s = new char[sublen];
	for (unsigned int i = 0; i < sublen; i++)
	{
		s[i] = str.str[subpos + i];
	}
	unsigned int t = compare(pos, len, s);
	delete[]s;
	return t;
}
int MyString::compare(const char* s) const
{
	return compare(0, strlen(s), s);
}
int MyString::compare(size_t pos, size_t len, const char* s) const
{
	if (pos + len > maxSize)
	{
		len = maxSize - pos;
	}
	char* substr = new char[len + 1];
	for (unsigned int i = 0; i<len; i++)
	{
		substr[i] = str[i];
	}
	substr[len] = '\0';
	unsigned int k = strcmp(substr, s);
	delete[]substr;
	return k;
}
int MyString::compare(size_t pos, size_t len, const char* s, size_t n) const
{
	if (n > strlen(s))
	{
		n = strlen(s);
	}
	char* substr = new char[n + 1];
	for (unsigned int i = 0; i < n; i++)
	{
		substr[i] = s[i];
	}
	substr[n] = '\0';
	unsigned int k = compare(pos, len, substr);
	delete[]substr;
	return k;
}

//-------------------Non-member function overloads:--------------------
MyString MyString::operator+(const MyString& rhs)
{
	return *this + rhs.str;
}
MyString MyString::operator+(const char* rhs)
{
	size_t len = maxSize + strlen(rhs);
	MyString newstr;
	newstr.reserve(len + 1);
	newstr.str = new char[newstr.str_capacity];
	newstr.maxSize = len;

	strcpy(newstr.str, str);
	strcpy(newstr.str + maxSize, rhs);

	return newstr;
}
MyString MyString::operator+(char c)
{
	char str[2];
	str[0] = c;
	str[1] = '\0';
	return *this + str;
}
MyString operator+ (const MyString& lhs, const MyString& rhs)
{
	MyString str(lhs);
	return str + rhs;
}
MyString operator+ (const MyString& lhs, const char* rhs)
{
	MyString str2(rhs);
	return lhs + str2;
}
MyString operator+ (const char* lhs, const MyString& rhs)
{
	MyString str2(lhs);
	return rhs + str2;
}
MyString operator+ (char c, const MyString& rhs)
{
	char str[2];
	str[0] = c;
	str[1] = '\0';
	return str + rhs;
}
MyString operator+ (const MyString& lhs, char c)
{
	char str[2];
	str[0] = c;
	str[1] = '\0';
	return lhs + str;
}
bool operator== (const MyString& lhs, const MyString& rhs)
{
	if (&lhs == &rhs)
		return 1;
	else
		return strcmp(lhs.str, rhs.str) == 0;
}
bool operator== (const char* lhs, const MyString& rhs)
{
	if (lhs == NULL || rhs.str == NULL)
		return 0;
	return strcmp(lhs, rhs.str) == 0;
}
bool operator== (const MyString& lhs, const char*   rhs)
{
	return rhs == lhs;
}
bool operator!= (const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}
bool operator!= (const char*   lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}
bool operator!= (const MyString& lhs, const char*   rhs)
{
	return !(lhs == rhs);
}
bool operator<  (const MyString& lhs, const MyString& rhs)
{
	if (strcmp(lhs.str, rhs.str) == -1)
		return true;
	return false;
}
bool operator<  (const char* lhs, const MyString& rhs)
{
	if (strcmp(lhs, rhs.str) == -1)
		return true;
	return false;
}
bool operator< (const MyString& lhs, const char*   rhs)
{
	if (strcmp(lhs.str, rhs) == -1)
		return true;
	return false;
}
bool operator<= (const MyString& lhs, const MyString& rhs)
{
	if (lhs.str == rhs)
		return true;
	if (strcmp(lhs.str, rhs.str) == -1)
		return true;
	return false;
}
bool operator<= (const char*   lhs, const MyString& rhs)
{
	if (lhs == rhs.str)
		return true; 
	if (strcmp(lhs, rhs.str) == -1)
		return true;
	return false;
}
bool operator<= (const MyString& lhs, const char* rhs)
{
	if (lhs.str == rhs)
		return true; 
	if (strcmp(lhs.str, rhs) == -1)
		return true;
	return false;
}
bool operator>(const MyString& lhs, const MyString& rhs)
{
	if (lhs == rhs.str)
		return true; 
	if (strcmp(lhs.str, rhs.str) == -1)
		return true;
	return false;
}
bool operator>(const char* lhs, const MyString& rhs)
{
	if (lhs == rhs.str)
		return true; 
	if (strcmp(lhs, rhs.str) == -1)
		return true;
	return false;
}
bool operator>(const MyString& lhs, const char*   rhs)
{
	if (lhs.str == rhs)
		return true;
	if (strcmp(lhs.str, rhs) == -1)
		return true;
	return false;
}
bool operator>= (const MyString& lhs, const MyString& rhs)
{
	if (lhs.str == rhs.str)
		return true; 
	if (strcmp(lhs.str, rhs.str) == -1)
		return true;
	return false;
}
bool operator>= (const char*   lhs, const MyString& rhs)
{
	if (lhs == rhs.str)
		return true; 
	if (strcmp(lhs, rhs.str) == -1)
		return true;
	return false;
}
bool operator>= (const MyString& lhs, const char*   rhs)
{
	if (lhs.str == rhs)
		return true; 
	if (strcmp(lhs.str, rhs) == -1)
		return true;
	return false;
}
void swap(MyString& x, MyString& y)
{
	if (&x == &y)
		return;
	MyString sub = x;
	x = y;
	y = sub;
}

istream& operator>> (istream& in, MyString& str)
{
	char buffer[256];
	in >> buffer;

	str.maxSize= strlen(buffer);
	str.str = new char[str.maxSize + 1];
	strcpy(str.str, buffer);

	return in;
}
ostream& operator<< (ostream& out, const MyString& str)
{
	out << str.str;
	return out;
}
istream& getline(istream& in, MyString& str, char delim)
{
	const size_t n = 256;
	char buffer[n];
	in.get(buffer, n, delim);

	str.maxSize = strlen(buffer);
	str.str = new char[str.maxSize + 1];
	strcpy(str.str, buffer);

	return in;
}
istream& getline(istream& in, MyString& str)
{
	return getline(in, str, '\n');
}