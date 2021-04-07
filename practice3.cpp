//Колокутин Георгий Геннадьевич, КМБО-06-20, вариант 11, практическая работа №2

/*
Необходимо реализовать указанную схему наследования. В схеме «0» А1 –
родитель для классов B1, B2.

  1 Каждый класс содержит защищённую переменную.
  Например: A1
содержит переменную a1, B1 – b1, C2 – c2 и т.п. Каждый класс имеет
конструктор, присваивающий этой переменной некое значение.
Конструкторы производных классов должны вызывать конструкторы
базовых классов и передавать туда параметры.

  2 В базовых классах реализовать функцию print(), которая выводит на
консоль имя класса, из которого она вызвана. В производных классах
переопределять её, чтобы она выводила корректный результат.

Например:
A1 a;
a.print(); => “A1”
B1 b;
b.print(); => “B1”
3 Написать функцию show(), которая выводит все доступные для этого
класса переменные. Например, в классе B1 доступны локальные
переменные класса B1 и некоторые переменные из родительского
класса A1. Переопределить её в производных классах.
A1 a;
a.show(); => только переменные в A1
B1 b;
b.show(); => переменные из B1 и A1
*/

//B2 <- A1 -> B1
//B2 <- A2 -> B1
//B2 <- A3 -> B1

#include <iostream>

using namespace std;

class A1
{
protected:
	int a1 = 0;
public:
	A1(int val = 0) : a1(val) {};
	void print() { cout << "\n \t -> A1\n"; }
	void show() { cout << "\nA1 = " << a1 << '\t'<< endl; }
};

class A2
{
protected:
	int a2 = 0;
public:
	A2(int val = 0) : a2(val) {};
	void print() { cout << "\n \t -> A2\n"; }
	void show() { cout << "\nA2 = " << a2 << '\t'<< endl; }
};

class A3
{
protected:
	int a3 = 0;
public:
	A3(int val = 0) : a3(val) {};
	void print() { cout << "\n \t -> A3\n"; }
	void show() { cout << "\nA3 = " << a3 << '\t'<< endl; }
};

class B1 : public A1, public A2, public A3
{
protected:
	int b1 = 0;
public:
	B1(int val, int val_2, int val_3, int val_4) : b1(val), A1(val_2), A2(val_3), A3(val_4) {};
	virtual void print() {
		cout << "\n\t ->B1\n";
	}
	virtual void show() {
		cout << "\nA1 = " << a1 << "\nA2 = " << a2 << "\nA3 = " << a3 << "\tB1 = " << b1 << endl;
	}
};

class B2 : public A1, public A2, public A3
{
protected:
	int b2 = 0;
public:
	B2(int val, int val_2, int val_3, int val_4) : b2(val), A1(val_2), A2(val_3), A3(val_4) {};
	virtual void print() {
		cout << "\n\t ->B2\n";
	}
	virtual void show() {
		cout << "\nA1 = " << a1 << "\nA2 = " << a2 << "\nA3 = " << a3 << "\tB2 = " << b2 << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "Ru-ru");

	B1 b1(5,4,3,2);
	b1.print();
	b1.show();

	B2 b2(9,8,7,6);
	b2.print();
	b2.show();

	A1* a11 = &b1;
	a11->print();
	a11->show();

	A1* a12 = &b2;
	a12->print();
	a12->show();

  A2* a21 = &b1;
	a21->print();
	a21->show();

	A2* a22 = &b2;
	a22->print();
	a22->show();

	A3* a31 = &b1;
	a31->print();
	a31->show();

	A3* a32 = &b2;
	a32->print();
	a32->show();


	return 0;
}
