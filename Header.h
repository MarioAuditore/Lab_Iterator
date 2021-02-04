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

	DequeIterator& operator++ ()
	{
		m_Ptr=m_Ptr->next;//��������� �� ���������
		return *this;
	}

	DequeIterator operator++ (int)
	{
		DequeIterator temp = *this;
		++(*this);//���������� ��� ��������� ����������
		return temp;
	}

	DequeIterator& operator-- ()
	{
		m_Ptr = m_Ptr->prev;//��������� �� ����������
		return *this;
	}

	DequeIterator operator-- (int)
	{
		DequeIterator temp = *this;
		--(*this);//���������� ��� ��������� ����������
		return temp;
	}

	ReferenceType operator[](int index)//�� ����������, �� � ������ ����� �� ������� ��� �� ������ ��������
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
		return m_Ptr == operand.m_Ptr;//������ ���������
	}

	bool operator!=(const DequeIterator& operand) const
	{
		return !(*this == operand);//���������� ��� ��������� �������� ==
	}

	PointerType m_Ptr;
};


template <typename Type>
class Deque {
public:
	class Node {
	public:
		Type data;
		Node* prev, * next; // ���������

		static Node* create(Type data) { // ������� �������� ������ �������� ������
			Node* newleaf = new Node;
			newleaf->data = data;
			newleaf->prev = newleaf->next = NULL;
			return newleaf;
		}
	};
	
	using ValueType = Node;
	using Iterator = DequeIterator<Deque<Type>>;//�.�. ������ ���������� ��� � Iterator

	Node* first;
	Node* last;
	int volume;

	Deque() { // ����������� �� ���������
		first = last = NULL;
		volume = 0;
	}

	//------------------���������------------------------------
	void swap(Deque* dq)//swap �������� ����� ��� �����, ������� �������� ����
	{
		int temp = this->volume;
		Iterator iter_end = this->end();
		Iterator iter_begin = this->begin();

		this->first = dq->first;
		this->last = dq->last;//������ ������ ������� Deque
		this->volume = dq->volume;

		dq->first = iter_begin.m_Ptr;
		dq->last = iter_end.m_Ptr;//� ������ �������
		dq->volume = temp;
	}
	
	Iterator begin() {
		return Iterator(first);//����� ���������� ������ �������
	}

	Iterator insert(Iterator pos, const Type& key)//insert, ������� ���������� ���������� pos
	{
		Node* newleaf = Node::create(key);
		newleaf->prev = pos.m_Ptr;
		newleaf->next = pos->next;//�������������� �����
		pos->next = newleaf;
		pos.m_Ptr = newleaf;
		return pos;
	}

	Iterator erase(Iterator pos)
	{
		Node* temp = pos->next;
		pos->prev->next = pos->next;//�������������� �����
		pos->next->prev = pos->prev;
		delete pos.m_Ptr;
		volume--;//��������� ������
		return temp;//������ ��������� ������
	}

	Iterator erase(Iterator begin, Iterator end)//��� �� erase �� ����� ���
	{
		while (begin != end)
		{
			begin = this->erase(begin);//��� ��� �� ����� ���� �� ������
		}
		return end;
	}

	bool IteratorIsEmpty(Iterator iter)
	{
		if (iter.m_Ptr != NULL)
		{
			return false;// ��� �������� deque �������� first � last ����� NULL
		}
		else
		{
			return true;
		}
	}


	Iterator end() {
		return Iterator(last);//������� ���������
	}
	//------------------���������------------------------------
	
	~Deque() {
		while (volume != 0) {
			Node* temp = first; // ����� �� �������� ���������
			first = temp->next; // ������ ������� -- ����� ������
			if (first == NULL) last = NULL; // ���� ��� ������ ���� �������, �� ���������� �� �����
			volume--;
			delete temp;
		}
		delete first, last;
	}

	bool isempty() {
		return (first == NULL); // �� �� �����, ��� � if (first == NULL)
	}// ������ ����� ����� �����

	int size() const { return volume; }

	void insertfirst(Type data) {
		Node* newleaf = Node::create(data);
		if (first == NULL) { // ���� ��� �������
			first = last = newleaf; // �� ������ � ��������� ��� �����
		}
		else { // ���� �� ����, �� ������������� �����
			first->prev = newleaf; // ���������� � ������� ����� �����
			newleaf->next = first; // ��������� � ������ -- ������
			first = newleaf;
			// ����� ���� ������
		}
		volume++; // ������� ���� -- �������� �����
	}
	
	void deletefirst() {
		if (isempty()) cout << "Deque is empty" << endl; // ���� �����, �� ������
		else {
			Node* temp = first; // ����� �� �������� ���������
			first = temp->next; // ������ ������� -- ����� ������
			if (first == NULL) last = NULL; // ���� ��� ������ ���� �������, �� ���������� �� �����
			volume--;
			delete temp;
		}
	}

	void insertlast(Type data) {
		if (isempty()) insertfirst(data); // ���� ������� �����, �� ������� ����������
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
		while (!isempty()) { // ���� ������� �� �����
			this->deletefirst(); // ������� ������ �������
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

	friend ostream& operator<<(ostream& os, Deque<Type>& deq) { // ���������� ��������� ������
		deq.show(); // ������ ������������ ������� ������ ����������� �� �����
		return os;
	}

	friend istream& operator>>(istream& is, Deque<Type>& deq) { // ���������� ��������� �����
		int n = 0;
		Type elem = 0;
		cout << "Enter the amount of elements in deque: ";
		cin >> n;
		for (int i = 0; i < n; i++) {
			cout << "Enter element: ";
			cin >> elem;
			deq.insertlast(elem); // ���������� ������ �������� ����� ���� � ����� ����
		}
		return is;
	}
};