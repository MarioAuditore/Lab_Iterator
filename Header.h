#pragma once
#include <iostream>

using namespace std;

class Node {};

template <typename Deque>
class DequeIterator
{
public:
	using ValueType = typename Deque::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

	DequeIterator(PointerType ptr)
		:m_Ptr(ptr) {};

	~DequeIterator()
	{
		this->m_Ptr = NULL;// по идее я не имею права освобождать память, ведь за это ответственен деструктор Деки
		//значит мне не остается ничего иного, кроме как занулить указатель и порвать связь итератора с контейнером
	}

	DequeIterator& operator++ ()
	{
		m_Ptr=m_Ptr->next;//указываем на следующий
		return *this;
	}

	DequeIterator operator++ (int)
	{
		DequeIterator temp = *this;
		++(*this);//используем уже сделанный префиксный
		return temp;
	}

	DequeIterator& operator-- ()
	{
		m_Ptr = m_Ptr->prev;//указываем на предыдущий
		return *this;
	}

	DequeIterator operator-- (int)
	{
		DequeIterator temp = *this;
		--(*this);//используем уже сделанный префиксный
		return temp;
	}

	ReferenceType operator[](int index)//не пригодился, но в теории может по индексу как бы давать значение
	{
		int i = 0;
		PointerType copy = m_Ptr;
		while (i < index)
		{
			copy = copy->next;
		}
		return *(copy);
	}


	PointerType operator->()
	{
		return m_Ptr;
	}

	ReferenceType operator*()
	{
		return *m_Ptr;
	}

	bool operator==(const DequeIterator& operand) const
	{
		return m_Ptr == operand.m_Ptr;//просто сравнение
	}

	bool operator!=(const DequeIterator& operand) const
	{
		return !(*this == operand);//используем уже созданный оператор ==
	}

	PointerType m_Ptr;
};


template <typename Type>
class Deque {
public:
	class Node {
	public:
		Type data;
		Node* prev, * next; // Указатели

		static Node* create(Type data) { // Функция создания нового листочка списка
			Node* newleaf = new Node;
			newleaf->data = data;
			newleaf->prev = newleaf->next = NULL;
			return newleaf;
		}
	};
	
	using ValueType = Node;
	using Iterator = DequeIterator<Deque<Type>>;//т.е. теперь обращаемся как к Iterator

	Node* first;
	Node* last;
	int volume;

	Deque() { // Конструктор по умолчанию
		first = last = NULL;
		volume = 0;
	}

	//------------------Итераторы------------------------------
	void swap(Deque* dq)//swap итератор юзаем как буфер, свапаем основные поля
	{
		int temp = this->volume;
		Iterator iter_end = this->end();
		Iterator iter_begin = this->begin();

		this->first = dq->first;
		this->last = dq->last;//меняем данные первого Deque
		this->volume = dq->volume;

		dq->first = iter_begin.m_Ptr;
		dq->last = iter_end.m_Ptr;//и данные второго
		dq->volume = temp;
	}
	
	Iterator begin() {
		return Iterator(first);//чисто возвращает первый элемент
	}

	Iterator insert(Iterator pos, const Type& key)//insert, который возвращает измененный pos
	{
		Node* newleaf = Node::create(key);
		newleaf->prev = pos.m_Ptr;
		newleaf->next = pos->next;//переобазначили связи
		pos->next = newleaf;
		pos.m_Ptr = newleaf;
		return pos;
	}

	Iterator erase(Iterator pos)
	{
		Node* temp = pos->next;
		pos->prev->next = pos->next;//переобазначили связи
		pos->next->prev = pos->prev;
		delete pos.m_Ptr;
		volume--;//уменьшаем размер
		return temp;//вернул следующий листок
	}

	Iterator erase(Iterator begin, Iterator end)//тот же erase но много раз
	{
		while (begin != end)
		{
			begin = this->erase(begin);//как раз до конца дело не дойдет
		}
		return end;
	}

	bool IteratorIsEmpty(Iterator iter)
	{
		if (iter.m_Ptr != NULL)
		{
			return false;// при создании deque значения first и last равны NULL
		}
		else
		{
			return true;
		}
	}


	Iterator end() {
		return Iterator(last);//вернули последний
	}
	//------------------Итераторы------------------------------
	
	~Deque() {
		/*
		while (volume != 0) {
			Node* temp = first; // Чтобы не потерять указатель
			first = temp->next; // Второй элемент -- новый первый
			if (first == NULL) last = NULL; // Если был только один элемент, то следующего не будет
			volume--;
			delete temp;
		}
		delete first, last;
		*/

		this->clear();
	}

	bool isempty() {
		return (first == NULL); // То же самое, что и if (first == NULL)
	}// Только сразу вернёт ответ

	int size() const { return volume; }

	void insertfirst(Type data) {
		Node* newleaf = Node::create(data);
		if (first == NULL) { // Если нет первого
			first = last = newleaf; // То первый и последний это новый
		}
		else { // Если же есть, то устанавливаем связи
			first->prev = newleaf; // Предыдущий у первого будет новый
			newleaf->next = first; // Следующий у нового -- первый
			first = newleaf;
			// Новый стал первым
		}
		volume++; // Добавил узел -- увеличил объем
	}
	
	void deletefirst() {
		if (isempty()) cout << "Deque is empty" << endl; // Если пуста, всё готово
		else {
			Node* temp = first; // Чтобы не потерять указатель
			first = temp->next; // Второй элемент -- новый первый
			if (first == NULL) last = NULL; // Если был только один элемент, то следующего не будет
			volume--;
			delete temp;
		}
	}

	void insertlast(Type data) {
		if (isempty()) insertfirst(data); // Если очередь пуста, то простое добавление
		else {
			Node* newleaf = Node::create(data);
			newleaf->prev = last;
			last->next = newleaf;
			last = newleaf;
			volume++;
		}
	}

	void deletelast() {
		if (isempty()) cout << "Deque is empty" << endl;
		else {
			Node* temp = last;
			last = temp->prev;
			if (last == NULL) first = NULL;
			volume--;
			delete temp;
		}
	}


	void clear() {
		if (isempty()) cout << "Deque is empty" << endl;
		while (!isempty()) { // Пока очередь не пуста
			this->deletefirst(); // Удаляем первый элемент
		}
	}

	void show() const {
		const Node* p = first;
		cout << "The volume of deque is: " << volume << endl;
		while (p != NULL) {
			cout << p->data << endl;
			p = p->next;
		}
	}

	friend ostream& operator<<(ostream& os, Deque<Type>& deq) { // Перегрузка оператора вывода
		deq.show(); // Просто используется функция вывода содержимого на экран
		return os;
	}

	friend istream& operator>>(istream& is, Deque<Type>& deq) { // Перегрузка оператора ввода
		int n = 0;
		Type elem = 0;
		cout << "Enter the amount of elements in deque: ";
		cin >> n;
		for (int i = 0; i < n; i++) {
			cout << "Enter element: ";
			cin >> elem;
			deq.insertlast(elem); // Добавление нового элемента будет идти в конец дека
		}
		return is;
	}
};
