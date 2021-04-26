// КМБО-06-20, Колокутин Георгий, 11 вариант.

#include <iostream>

using namespace std;

class BaseString
{
protected:
	char* p;
	int len;
	int capacity;
public:
	BaseString(char* ptr)
	{
		// Проверяем ptr != nullptr
		cout << "\nBase Constructor 1\n";
		capacity = 256;
		p = new char[capacity];
		len = 0;
		int i = 0;
		p[0] = '\0';
		if (ptr != nullptr) {
			while (ptr[i] != '\0' && i < capacity - 1) {
				p[i] = ptr[i];
				++i;
			}
			p[i] = '\0';
			len = i;
		}
	}
	BaseString(const char* ptr)
	{
		cout << "\nBase Constructor 1\n";
		capacity = 256;
		p = new char[capacity];
		len = 0;
		int i = 0;
		p[0] = '\0';
		if (ptr != nullptr) {
			while (ptr[i] != '\0' && i < capacity - 1) {
				p[i] = ptr[i];
				++i;
			}
			p[i] = '\0';
			len = i;
		}
	}

	BaseString(int Capacity = 256)
	{
		cout << "\nBase Constructor 0\n";
		capacity = Capacity;
		p = new char[capacity];
		len = 0;
	}

	~BaseString()
	{
		cout << "\nBase Destructor\n";
		if (p != NULL)
			delete[] p;
		len = 0;
	}

	int Length() { return len; }
	int Capacity() { return capacity; }
	char& operator[](int i) { return p[i]; }


	BaseString& operator=(BaseString& s)
	{
		cout << "\nBase Operator = \n";
		if (capacity >= s.capacity) {
			len = s.len;
			for (int i = 0; i <= len; ++i) {
				p[i] = s.p[i];
			}
		}
		else {
			delete[] p;
			capacity = s.capacity;
			len = s.len;
			p = new char[capacity];
			for (int i = 0; i <= len; ++i) {
				p[i] = s.p[i];
			}
		}

		return *this;
	}

	BaseString(const BaseString& s)
	{
		cout << "\nBase Copy Constructor\n";
		capacity = s.capacity;
		len = s.len;
		p = new char[capacity];

		for (int i = 0; i < len; ++i) {
			p[i] = s.p[i];
		}
		p[len] = '\0';
	}

	virtual void print()
	{
		int i = 0;
		while (p[i] != '\0')
		{
			cout << p[i];
			i++;
		}
		cout << endl;
	}
};


class String : public BaseString {

public:
	String(char* s) : BaseString(s) {}
	String(const char* s) : BaseString(s) {}
	String(int Capacity = 256) : BaseString(Capacity) {}

	String operator=(const String& s)
	{
		cout << "\nBase Operator = \n";
		if (capacity >= s.capacity) {
			len = s.len;
			for (int i = 0; i <= len; ++i) {
				p[i] = s.p[i];
			}
		}
		else {
			delete[] p;
			capacity = s.capacity;
			len = s.len;
			p = new char[capacity];
			for (int i = 0; i <= len; ++i) {
				p[i] = s.p[i];
			}
		}

		return *this;
	}

	String(const String& s)
	{
		cout << "\nBase Copy Constructor\n";
		capacity = s.capacity;
		len = s.len;
		p = new char[capacity];

		for (int i = 0; i < len; ++i) {
			p[i] = s.p[i];
		}
		p[len] = '\0';
	}

	bool endswith(string ending) {
		int s = ending.size();
		int LengthOfThis = Length() - 1;
		for (int i = 0; i < s; i++) {
			if (p[LengthOfThis] == ending[i]) {
				cout << ("true") << endl;
				return true;
			}
		}

	}
};


int main()
{
	String a1("asdfgda");
	String a2("g");
	String a3("fds");
	String a4("adsufkjla");
	a4.print();
	a4.endswith("qwace");
	cout << "\n";
	int m; cin >> m;
}
