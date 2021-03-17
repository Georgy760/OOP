//Колокутин Георгий Геннадьевич, КМБО-06-20, вариант 11, практическая работа №2
#include <iostream>

using namespace std;





 //Конст. копирования и оператор = везде FIX!!!!!!!!!!!!!!!!!!!!!!!!!!




class MyArrayParent
{
protected:
	//сколько памяти выделено?
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	double* ptr;
public:
	//конструкторы и деструктор
	MyArrayParent(int Dimension = 100)
	{
		cout << "\nMyArrayParent constructor\n";
		ptr = new double[Dimension]; // выделяем память с помощью new
		capacity = Dimension;
		count = 0;
	}
	//конструктор принимает существующий массив
	MyArrayParent(double* arr, int len)
	{
		cout << "\nMyArrayParent constructor\n";
		//заполнить массив ptr, заполнить поля
	}
	//деструктор
	~MyArrayParent()
	{
		cout << "\nMyArrayParent destructor\n";
		if (ptr != NULL)
		{
			delete[] ptr; // освобождаем свободную память
			ptr = NULL;
		}
	}

	//обращение к полям
	int Capacity() { return capacity; }
	int Size() { return count; }

	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		//сгенерировать исключение, если индекс неправильный
		return -1;
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
		//сгенерировать исключение, если индекс неправильный
	}

	//добавление в конец нового значения (сложность О(1))
	void push(double value)
	{
		if (capacity > count)
		{
			ptr[count] = value;
			count += 1;
		}
		else
			return;
	}

	//удаление элемента с конца
	void RemoveLastValue()
	{
		if (count > 0)
			count -= 1;
		//что делаем, если пуст? - ничего
	}

	double& operator[](int index)
	{
		//перегрузка оператора []
		// cout<<arr[2]; считывание
		// arr[2] = 1; - запись
		// если не писать ссылку, то будет менятся ссылка, а не оригинал
		if (index < 0)
			return ptr[count + index];
		if (count > index)
			return ptr[index];
	}

	MyArrayParent& operator=(const MyArrayParent& V) //оператор =
	{

		capacity = V.capacity;
		count = V.count;

		ptr = new double[V.capacity];
		for (int i = 0; i < V.count; i++)
			ptr[i] = V.ptr[i];
		return *this;
	}

	MyArrayParent(const MyArrayParent& V)
	{
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
		capacity = V.capacity;
		count = V.count;

		ptr = new double[V.capacity];
		for (int i = 0; i < V.count; i++)
			ptr[i] = V.ptr[i];
	}

	void print()
	{
		cout << "\nMyArrParent, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}

};

class MyArrayChild : public MyArrayParent
{
public:
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor\n"; }

	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	//удаление элемента
	void RemoveAt(int index)
	{
		if (abs(index) < count)
		{
			if (index >= 0)
			{
				for (int i = index; i < count; i++)
				{
					ptr[i] = ptr[i + 1];
				}
				count -= 1;
			}
			if (index < 0)
			{
				for (int i = count + index; i < count; i++)
				{
					ptr[i] = ptr[i + 1];
				}
			}
		}
	}

	int FindZeros() { //поиск нулей
		int* zeros;
		int count_zeros = 0;
		int counter = 0;

		for (int i = 0; i < count; i++) {
			if (ptr[i] == 0) count_zeros++;
		}
		//cout << "count_zeros: " << count_zeros << endl;
		zeros = new int[count_zeros];

		for (int j = 0; j < count; j++) {
			if (ptr[j] == 0) {
				zeros[counter] = j;
				counter++;
			}

		}


		return count_zeros; //возвращает кол. нулей
	}
	void RemoveZeros() { //удаление нулей (чистка)
		int count_zeors = FindZeros();
		while (count_zeors != 0) {
			int zero = 0;
			for (int i = 0; i < count; i++) {
				if (ptr[i] == 0) {
					zero = i;
				}
			}
			RemoveAt(zero);
			//cout << "Zero was removed from index: " << zero << endl;
			count_zeors--;
		}

	}

	//поиск элемента
	// линейный поиск стоит О(n)
	int IndexOf(double value, bool bFindFromStart)
	{
		if (bFindFromStart == false) // линейный поиск
		{
			for (int i = 0; i < count; i++)
				if (ptr[i] == value)
					return i;
			return -1;
		}
	}

	//вставка элемента
	void InsertAt(double value, int index)
	{
		if (index > 0)
		{
			for (int i = count - 1; i >= index; i--)
			{
				ptr[i + 1] = ptr[i];
			}
			ptr[index] = value;
			count++;
		}
	}

	MyArrayChild diff(double diff, MyArrayChild &V) {
		cout << "\n---------DIFF START---------\n" << endl;
		double avr = 0.0;
		for (int i = 0; i < count; i++) {
			avr += ptr[i];
		}
		avr = avr / count;
		cout << "\nAverage: " << avr;
		cout << "\nDiff: ";
		cout << (avr - diff) << " " << (avr + diff);
		for (int i = 0; i < count; i++) {
			if ((ptr[i] >= (avr + diff)) || (ptr[i] <= (avr - diff))) {
				V.ptr[i] = 0;


			}
			else {
				cout << "\nDiff elements: " << ptr[i] << endl;

			}
		}
		V.RemoveZeros();
		V.print();
		cout << "\n---------DIFF END---------\n" << endl;
		return V;
	}


};

class MySortedArray : public MyArrayChild
{
protected:
	double* a;

	int IndexOf_1(double value, bool bFindFromStart)// бинарный поиск
	{
		if (bFindFromStart == true)
		{
			int l = 0;
			int r = count;
			int mid;

			while (l <= r)
			{
				mid = (l + r) / 2;
				if (ptr[mid] == value)
					return mid;
				if (value < ptr[mid])
					r = mid - 1;
				if (value > ptr[mid])
					l = mid + 1;
			}
			return mid;
		}
	}

public:
	MySortedArray(int Dimension = 100)
	{
		ptr = new double[Dimension]; // выделяем память с помощью new
		a = new double[Dimension];
		capacity = Dimension;
		count = 0; cout << "\nMyArrayChild constructor";
	}

	~MySortedArray()
	{
		if (ptr != NULL)
		{
			delete[] ptr; // освобождаем свободную память
			ptr = NULL;
		}
		if (a != NULL)
		{
			delete[] a; // освобождаем свободную память
			a = NULL;
		}
		cout << "\nMySortedArray destructor\n";
	}

	// бинарный поиск стоит О(log(n)) - если массив отсортирован
	int IndexOf(double value, bool bFindFromStart)// бинарный поиск
	{
		if (bFindFromStart == true)
		{
			int l = 0;
			int r = count;
			int mid;

			while (l <= r)
			{
				mid = (l + r) / 2;
				if (ptr[mid] == value)
					return mid;
				if (value < ptr[mid])
					r = mid - 1;
				if (value > ptr[mid])
					l = mid + 1;
			}
			return -1;
		}
	}

	MySortedArray diff(double diff, MySortedArray& V) { //Выделить все элементы, отличающиеся от среднего арифметического в массиве не более, чем на параметр функции diff
		cout << "\n---------DIFF START---------\n" << endl;
		double avr = 0.0;
		for (int i = 0; i < count; i++) {
			avr += ptr[i];
		}
		avr = avr / count;
		cout << "\nAverage: " << avr;
		cout << "\nDiff: ";
		cout << (avr - diff) << " " << (avr + diff);
		for (int i = 0; i < count; i++) {
			if ((ptr[i] >= (avr + diff)) || (ptr[i] <= (avr - diff))) {
				V.ptr[i] = 0;


			}
			else {
				cout << "\nDiff elements: " << ptr[i] << endl;

			}
		}
		V.RemoveZeros();
		V.print();
		cout << "\n---------DIFF END---------\n" << endl;
		return V;
	}

	void push(double x)
	{

		if (count == 0)
		{
			ptr[count] = x;
			count += 1;
		}
		else
		{
			int index = IndexOf_1(x, true);
			InsertAt(x, index);
		}
	}



};

int main()
{
	//MyArrayParent arr;
	MySortedArray arr;
	for (int i = 0; i < 10; i++)
	{
		arr.push(i + 1);
	}
	arr.push(6);
	//arr.print();
	//
	cout << "\n" << arr.IndexOf(15, true);
	cout << "\n";

	MyArrayChild array;
	for (int i = 0; i < 10; i++)
	{
		array.push(i + 1);
	}
	array.print();
	cout << "\n-----------------------------------------------" << endl;
	arr.print();
	MySortedArray arr1(arr);
	arr1.diff(3, arr1);
	arr1.print();
	cout << "\n-----------------------------------------------" << endl;
	array.print();
	MyArrayChild a(array);
	a.print();
	array.diff(3, a);
	array.print();
	char c; cin >> c;

	return 0;

}

/*
Вам предоставлен класс MyArrayParent, частично реализующий функции массива
(файл InheritanceArray_empty.cpp). Дополните класс необходимыми функциями:
1 Конструктором копий MyArrayParent (&MyArrayParent v).
2 Оператором =.
3 Оператором [ ] для обращения к элементу по индексу.
4 Конструктором, принимающим и копирующим информацию из существующего
массива.
B. В классе MyArrayChild, унаследованном от класса MyArrayParent, необходимо
добавить функции (обратите внимание на то, что можно пользоваться функциями, уже
реализованными в базовом классе):
1 Удаления элемента из произвольного места в массиве RemoveAt().
2 Поиска элемента в массиве по значению IndexOf().
3 Вставки элемента в некоторое место в массиве InsertAt().
4 Добавьте функцию согласно Вашему варианту (см. таблицу 1). Результатом
обработки массива должен быть новый объект класса. Исходный массив не должен
меняться.
C. Унаследуйте новый класс MySortedArray от MyArrayChild. Мы предполагаем, что этот
класс содержит упорядоченный массив. Переопределите функции из пункта B.4, имея
ввиду, что массив отсортирован. Переопределите операцию добавления элемента (push)
таким образом, чтобы массив оставался отсортированным при добавлении нового
элемента



11 Вариант: выделить все элементы, отличающиеся от среднего арифметического в массиве не более, чем на параметр функции diff
*/
