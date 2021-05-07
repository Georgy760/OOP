//Колокутин Георгий Геннадьевич, КМБО-06-20, вариант 11, практическая работа №6
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


/*
Для хранения года выпуска создан простейший класс даты.
Входные данные в нём не проверяются на коректность, все поля публичные.
*/
class Date {
public:
	int year;
	int mounth;
	int day;
	Date(int d = 1, int m = 1, int y = 2000) {
		day = d;
		mounth = m;
		year = y;
	}
	friend ostream& operator<<(ostream& s, const Date& d);
	friend istream& operator>>(istream& s, Date& d);
};
ostream& operator<<(ostream& s, const Date& d) {
	if (typeid(s) == typeid(ofstream)) {
		s << d.day << " " << d.mounth << " " << d.year;
	}
	else {
		s << d.day << "." << d.mounth << "." << d.year;
	}

	return s;
}
istream& operator>>(istream& s, Date& d) {
	if (typeid(s) == typeid(ifstream)) {
		string line;
		getline(s, line);
		std::istringstream iss(line);
		iss >> d.day >> d.mounth >> d.year;

	}
	s >> d.day >> d.mounth >> d.year;
	return s;
}



/*
«Альбом».
Поля: имя автора, название, дата выпуска, кол. композиций.
*/
class Album {
protected:

public:
	// Так как я всё-равно не осуществяю проверку корректности вводимых данных, а геттеров/сеттеров пришлось бы писать много, данные о альбоме будут public, а не protected
	string name;
	string lable;
	Date date_of_publish;
	int quantity;

	Album(string i_name = "Николай", string i_lable = "Альбом #1", Date i_date_of_publish = Date(), int i_quantity = 1) {
		name = i_name;
		lable = i_lable;
		date_of_publish = i_date_of_publish;
		quantity = i_quantity;
		//cout << __FUNCTION__ << endl;
	}

	Album(const Album& p) {
		cout << __FUNCTION__ << endl;
		name = p.name;
		lable = p.lable;
		date_of_publish = p.date_of_publish;
		quantity = p.quantity;
	}
	Album& operator=(const Album& p) {
		//cout << __FUNCTION__ << endl;
		name = p.name;
		lable = p.lable;
		date_of_publish = p.date_of_publish;
		quantity = p.quantity;
		return *this;
	}

	~Album() {
	}
	friend ostream& operator<<(ostream& s, const Album& p);
	friend istream& operator>>(istream& s, Album& p);
};


ostream& operator<<(ostream& s, const Album& p) {
	if (typeid(s) == typeid(ofstream)) {
		s << p.name << "\n" << p.lable << "\n" << p.date_of_publish << "\n" << p.quantity;
	}
	else {
		s << "Псевдоним: " << p.name << "\nНазвание альбома: " << p.lable 
			<< "\nДата выпуска: " << p.date_of_publish << "\nКоличество композиций: " << p.quantity;

	}
	return s;
}

istream& operator>>(istream& s, Album& p) {
	if (typeid(s) == typeid(ifstream)) {

		string line;

		getline(s, p.name);
		getline(s, p.lable);

		getline(s, line);
		std::istringstream iss1(line);
		iss1 >> p.date_of_publish;

		getline(s, line);
		std::istringstream iss2(line);
		iss2 >> p.quantity;

	}
	else {
		cout << "Bad Readed:\n" << p << endl;
		s >> p.name >> p.lable >> p.date_of_publish >> p.quantity;
	}

	return s;
}


/*
Шаблонный класс элемента связного списка.
В моём варианте поле info будет иметь тип Album.
*/
template<class T>
class Element
{
public:
	T info;
	Element* next;
	Element* prev;
	Element() {
		next = prev = nullptr;
	}
	/*Element(T data)
	{
		next = prev = NULL;
		info = data;
	}*/

	Element(const T& data)
	{
		//cout << __FUNCTION__ << endl;
		next = prev = NULL;
		info = data;
	}

	Element(Element* Next, Element* Prev, T data)
	{
		//cout << __FUNCTION__ << endl;
		next = Next;
		prev = Prev;
		info = data;
	}

	Element(const Element& el)
	{
		//cout << __FUNCTION__ << endl;
		next = el.next;
		prev = el.prev;
		info = el.info;
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, const Element<T1>& el);
	template<class T1>
	friend istream& operator>>(istream& s, Element<T1>& el);

};

template<class T1>
ostream& operator<<(ostream& s, const Element<T1>& el)
{
	s << el.info;
	return s;
}

template<class T1>
istream& operator>>(istream& s, Element<T1>& el)
{
	s >> el.info;
	return s;
}


/*
Исключение неверного индекса
*/
class IndexOutOfRangeException : public exception {
protected:
	string error_info;
public:
	IndexOutOfRangeException(string in) : exception() {
		error_info = in;
	}
	void print() const {
		cout << this->error_info << endl;
	}
};


/*
Шаблонный класс связного списка
*/
template<class T>
class LinkedList
{
protected:
	Element<T>* head = nullptr;
	Element<T>* tail = nullptr;
	int count = 0;
public:

	LinkedList()
	{
		//cout << __FUNCTION__ << endl;
		head = tail = nullptr;
		count = 0;
	}

	//LinkedList(T* arr, int len){}

	virtual ~LinkedList()
	{
		cout << __FUNCTION__ << endl;
		Element<T>* cur = this->head;
		while (cur != nullptr) {
			Element<T>* to_delete = cur;
			cur = cur->next;
			delete to_delete;
		}
		this->head = nullptr;
		this->count = 0;
		this->head = nullptr;
	}

	virtual Element<T>* pop() = 0;
	virtual Element<T>* push(const T& value) = 0;

	// Рекурсивное получение i-го элемента связного списка
	Element<T>* operator()(int index, int cur_index = 0, Element<T>* p = nullptr) {
		if (cur_index == 0 && p == nullptr) {
			p = this->head;
		}
		if (p != nullptr && cur_index < this->count && index >= cur_index) {
			if (cur_index == index) {
				return p;
			}
			else {

				return operator()(index, cur_index + 1, p->next);
			}
		}
		else {
			return nullptr;
		}
	}

	Element<T>& operator[](int index)
	{
		if (index < 0 || index >= count) {
			throw IndexOutOfRangeException(string("index = " + to_string(index) + ", count of elements = " + to_string(count)));
		}

		Element<T>* current = head;

		for (int i = 0;
			current != NULL && i < index;
			current = current->next, i++);

		return *current;
	}

	virtual bool isEmpty() const {
		return (this->count == 0);
	}

	virtual int get_count() {
		return this->count;
	}
	virtual Element<T>* get_head() {
		return this->head;
	}
	virtual Element<T>* get_tail() {
		return this->tail;
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, const LinkedList<T1>& el);
	template<class T1>
	friend istream& operator>>(istream& s, const LinkedList<T1>& el);
};

template<class T1>
ostream& operator<<(ostream& s, const LinkedList<T1>& el)
{
	Element<T1>* current;
	for (current = el.head; current != NULL; current = current->next)
		s << *current << " ";
	return s;
}

template<class T1>
istream& operator>>(istream& s, const LinkedList<T1>& el)
{
	for (Element<T1>* current = el.head; current != NULL; current = current->next)
		s >> *current;
	return s;
}


/*
Добавление: в конец (стек)
Удаление: с конца (стек)
*/
template <typename T1>
class Stack : public LinkedList<T1> {
public:
	Stack() : LinkedList<T1>() {
		//cout << __FUNCTION__ << endl;
	}

	virtual ~Stack() {
		cout << __FUNCTION__ << endl;

		Element<T1>* cur = this->head;
		while (cur != nullptr) {
			Element<T1>* to_delete = cur;
			cur = cur->next;
			delete to_delete;
		}
		this->head = nullptr;
		this->count = 0;
		this->head = nullptr;
	}

	// В базовом классе не было конструктора копий
	Stack(const Stack& in) {
		//cout << __FUNCTION__ << endl;
		this->count = 0;
		Element<T1>* cur_in = in.head;
		Element<T1>* cur_this = nullptr;
		while (cur_in != nullptr) {

			if (cur_this == nullptr) {
				cur_this = new Element<T1>(*cur_in);
				this->head = cur_this;
				cur_in = cur_in->next;
			}
			else {
				cur_this->next = new Element<T1>(*cur_in);
				cur_this->next->prev = cur_this;
				cur_this = cur_this->next;
				cur_in = cur_in->next;
			}
			++(this->count);
		}
		this->tail = cur_this;
	}

	Stack& operator=(const Stack& in) {
		//cout << __FUNCTION__ << endl;
		this->clear();
		this->count = 0;
		Element<T1>* cur_in = in.head;
		Element<T1>* cur_this = nullptr;
		while (cur_in != nullptr) {

			if (cur_this == nullptr) {
				cur_this = new Element<T1>(*cur_in);
				this->head = cur_this;
				cur_in = cur_in->next;
			}
			else {
				cur_this->next = new Element<T1>(*cur_in);
				cur_this->next->prev = cur_this;
				cur_this = cur_this->next;
				cur_in = cur_in->next;
			}
			++(this->count);
		}
		this->tail = cur_this;
		return *this;
	}


	// Удаляет последний элемент, НЕ очищая память из-под него. Возвращает указатель на него.
	Element<T1>* pop() {
		if (this->isEmpty()) {
			return nullptr;
		}

		Element<T1>* ans = this->tail;

		if (this->count == 1) {
			this->head = nullptr;
			this->tail = nullptr;
		}
		else {
			this->tail = this->tail->prev;
			this->tail->next = nullptr;
		}
		--(this->count);
		ans->prev = nullptr;
		return ans;

	}

	// Добавление элемента в конец
	Element<T1>* push(const T1& value) {
		if (this->isEmpty()) {
			this->head = new Element<T1>(value);
			this->tail = this->head;
			this->head->next = nullptr;
			this->head->prev = nullptr;
		}
		else {
			this->tail->next = new Element<T1>(value);
			this->tail->next->prev = this->tail;
			this->tail = this->tail->next;
		}
		++(this->count);
		return this->tail;
	}

	// Вставка на i-ое место
	Element<T1>* insert(const T1& value, int index) {
		if (index < 0) {
			throw IndexOutOfRangeException("Index < 0");
		}
		else if (index <= this->count) {
			Element<T1>* cur = this->head;
			int cur_num = 0;

			while (cur_num < index) {
				cur = cur->next;
				++cur_num;
			}

			// Вставка в начало
			if (cur == this->head) {
				Element<T1>* old = this->head;
				this->head = new Element<T1>(value);
				this->head->next = old;
				old->prev = this->head;
				++(this->count);
				return this->head;
			}
			// Вставка между началом и концом
			else if (cur != nullptr) {
				Element<T1>* old_prev = cur->prev;

				cur->prev = new Element<T1>(value);
				cur->prev->next = cur;
				cur->prev->prev = old_prev;
				old_prev->next = cur->prev;
				++(this->count);
				return cur->prev;
			}
			// Вставка после хвоста
			else {
				this->tail->next = new Element<T1>(value);
				this->tail->next->prev = this->tail;
				this->tail = this->tail->next;
				++(this->count);
				return this->tail;
			}
		}
		else {
			throw IndexOutOfRangeException("Index > len(Stack)");
		}

	}

	// Удаляет i-ый элемент, очищая память
	Element<T1> remove(int index) {
		if (index < 0) {
			throw IndexOutOfRangeException("Index < 0");
		}
		else if (index < this->count) {
			Element<T1>* cur = this->head;
			int cur_num = 0;

			while (cur_num != index) {
				cur = cur->next;
				++cur_num;
			}
			Element<T1>* c_prev = cur->prev;
			Element<T1>* c_next = cur->next;

			if (cur == this->head) {
				this->head = this->head->next;
			}
			if (cur == this->tail) {
				this->tail = this->tail->prev;
			}

			Element<T1> ans(*cur);
			ans.next = nullptr; ans.prev = nullptr;

			delete cur; cur = nullptr;

			if (c_prev != nullptr)
				c_prev->next = c_next;
			if (c_next != nullptr)
				c_next->prev = c_prev;

			--(this->count);
			return ans;

		}
		else {
			throw IndexOutOfRangeException("Index > tail index");
		}
	}

	// Удаляет все элементы, очищая память
	void clear() {
		while (!this->isEmpty()) {
			Element<T1>* ptr = this->pop();
			delete ptr;
		}
	}

	// Удаляет все элементы, очищая память, и печатая их
	void print_and_clear() {
		while (!this->isEmpty()) {
			Element<T1>* ptr = this->pop();
			cout << ptr->info << "\n\n";
			delete ptr;
		}
	}

	// поиск по названию, фильтр по имени автора, принимающий функцию
	template<typename T2>
	Stack filter(bool (*criterion)(const T1& value_to_comparison, const T2 param), const T2 param_for_search_in_value) {
		Stack<T1> ans;
		Element<T1>* cur = this->head;
		while (cur != nullptr) {
			if (criterion(cur->info, param_for_search_in_value)) {
				ans.push(cur->info);
			}
			cur = cur->next;
		}
		return ans;
	}

	// Рекурсивная реализация функции фильтра
	template<typename T2>
	Stack<T1>* filter_recursive(bool (*criterion)(const T1& value_to_comparison, const T2 param), const T2 param_for_search_in_value,
		Element<T1>* start_from = nullptr, Stack<T1>* stack_for_ans = nullptr) {

		// Инициализация если последние 2 параметра не передали
		if (stack_for_ans == nullptr && start_from == nullptr) {
			start_from = this->head;
			stack_for_ans = new Stack<T1>;
		}

		// Инициализация, если не дали только последний параметр
		if (stack_for_ans == nullptr) {
			stack_for_ans = new Stack<T1>;
		}

		// База рекурсии
		if (start_from == nullptr) {
			return stack_for_ans;
		}

		// Добавление элемента
		if (criterion(start_from->info, param_for_search_in_value)) {
			stack_for_ans->push(start_from->info);
		}

		return filter_recursive(criterion, param_for_search_in_value, start_from->next, stack_for_ans);
	}

	void save_to(ofstream& s) {
		s << this->count << endl;
		Element<T1>* cur = this->head;
		for (int i = 0; i < this->count; ++i) {
			s << (*cur) << endl;
			cur = cur->next;
		}
	}

	void load_from(ifstream& s) {
		this->clear();

		int count_of_elements;
		string line;
		getline(s, line);
		std::istringstream iss(line);
		iss >> count_of_elements;
		for (int i = 0; i < count_of_elements; ++i) {
			T1 cur;
			s >> cur;
			this->push(cur);
		}

	}
};

// Функция проверки равенства названий
bool lable_search(const Album& p, const string param_for_search_in_value = "") {
	if (p.lable == param_for_search_in_value) {
		return true;
	}
	else {
		return false;
	}
}

// Функция проверки равенства имён
bool name_search(const Album& p, const string param_for_search_in_value = "") {
	if (p.name == param_for_search_in_value) {
		return true;
	}
	else {
		return false;
	}
}


void set_hex_manip(ostream& f) {
	f << hex << uppercase;
}


int main()
{
	setlocale(LC_ALL, "Russian");

	try
	{
		Stack<Album> s;
		s.push(Album());
		s.push(Album("Сидоров"));
		s.push(Album("Козлов"));

		s.remove(1);


		s.insert(Album("Insert"), 2);


		Stack<Album>* s2 = s.filter_recursive(lable_search, string("Иванов"));
		Stack<Album> s3 = s.filter(name_search, string("Иванов"));


		cout << "\n~~~Изначальный список~~~\n";
		s.print_and_clear();
		cout << "\n~~~Рекурсивно отфильтрованный список s2~~~\n";
		s2->print_and_clear();
		cout << "\n~~~Отфильтрованный список s3~~~\n";
		s3.print_and_clear();

		cout << "\n~~~Изначальный список~~~\n";
		s.push(Album("Сидоров"));
		s.push(Album("АААА", "FFF", Date(), 3));
		s3 = s.filter(name_search, string("Иванов"));
		s.print_and_clear();
		cout << "\n~~~Отфильтрованный список~~~\n";
		s3.print_and_clear();
	}
	catch (const IndexOutOfRangeException& e)
	{
		e.print();
	}

	cout << "\n~~~No cast~~~\n";
	LinkedList<Album>* base_class_ptr = new Stack<Album>;
	delete base_class_ptr;

	cout << "\n~~~dynamic_cast~~~\n";
	LinkedList<Album>* ptr_to_cast = new Stack<Album>;
	Stack<Album>* casted = dynamic_cast<Stack<Album>*>(ptr_to_cast);
	delete casted;


	Stack<Album> s_to_file;
	Stack<Album> s_from_file;
	s_to_file.push(Album()); s_to_file.push(Album("Виталий", "Альбом #2", Date(10, 9, 2000), 100)); s_to_file.push(Album());
	
	string file_name = "Practice6.txt";
	ofstream fout(file_name);

	if (fout.is_open()) {
		s_to_file.save_to(fout);
		fout.close();
	}
	else {
		std::cout << "file not opened\n";
	}
	ifstream fin(file_name);

	if (fin.is_open()) {
		s_from_file.load_from(fin);
		fin.close();
	}
	else {
		std::cout << "file not opened\n";
	}
	cout << "\n~~~Readed from file~~~\n";
	s_from_file.print_and_clear();

	set_hex_manip(cout);
	Stack<Album> s4;
	s4.push(Album("Тимур", "Альбом #3", Date(10, 9, 1990), 128));
	s4.print_and_clear();
	//Album(string i_name = "Иван", string i_lable = "Альбом 1", Date i_date_of_publish = Date(), int i_quantity = 1)
	return 0;
}
