#pragma once
#include <stdlib.h>

template <class Type>
class Node {
private:
	Type var;
	Node<Type> *next;
	Node<Type> *previous;

public:
	void SetVar(Type x) {
		var = x;
	}

	void SetNext(Node<Type> *n) {
		next = n;
	}

	void SetPrevious(Node<Type> *n) {
		previous = n;
	}

	Node<Type>* GetNext() {
		return next;
	}

	Node<Type>* GetPrevious() {
		return previous;
	}

	Type GetVar() {
		return var;
	}

	Node() {
		SetVar(Type());
		SetNext(NULL);
		SetPrevious(NULL);
	}

	Node(Type x) {
		SetVar(x);
		SetNext(NULL);
		SetPrevious(NULL);
	}
	Node(Type x, Node<Type>* p, Node<Type>* n) {
		SetVar(x);
		SetNext(n);
		SetPrevious(p);
	}
};

template <class Type>  
class List
{
private:

	Node<Type>* head;

	int length;

public:
	List()
	{
		head = NULL;
		length = 0;
	}
	Node<Type>* GetHead()
	{
		return head;
	}
	int GetLength()
	{
		return length;
	}
	void SetLength(int i)
	{
		if (i>0) length = i;
	}

	Node<Type>* Search(int pos) {
		if (pos<0 || pos>length) {
			throw("Выход за границы списка");
		}
		Node<Type>* current = head;
		for (int i = 0; i < pos; i++) {
			current = current->GetNext();
		}
		return current;
	}

	void InsertBeforHead(Type x) { 
		if (length == 0)
		{
			head = new Node<Type>(x);
		}
		else
		{
			Node<Type>* temp;
			temp = new Node<Type>(x, NULL, head);
			head->SetPrevious(temp);
			head = temp;
		}
		length++;
	}
	void InserеtInTail(Type x) { 
		Node<Type>* current = Search(length-1);

		Node<Type>* temp = new Node<Type>(x, current, NULL);
		current->SetNext(temp);

		length++;
	}
	//Вставка в указанную позицию
	void Insert(Type x, int pos) 
	{
		if (pos<0) {
			throw("Ошибка в позиции");
		}
		if (pos>=length+1) {
			throw("Выход за границы списка");
		}
		if (pos == 0)
		{
			InsertBeforHead(x);
			return;
		}
		if (pos==length) {
			InserеtInTail(x);
			return;
		}
		Node<Type>* current = Search(pos);
		Node<Type>* temp = new Node<Type>(x, current->GetPrevious(), current);
		current->GetPrevious()->SetNext(temp);
		temp->SetNext(current);
		length++;
	}
	//Вставка элемента в конец без указания позиции
	void Insert(Type x) {
		if (length == 0) {
			InsertBeforHead(x);
			return;
		}
		InserеtInTail(x);
	}
	//Упорядоченная вставка элемнета в список
	void InsertOrdered(Type x) { // в доработке
		Node<Type>* current = head;

		Node<Type>* temp = new Node<Type>(x);

		if (current == NULL) {
			Insert(x);
			return;
		}
		if (x < current->GetVar())
		{
			InsertBeforHead(x);
			return;
		}

		while (x > current->GetVar())
		{
			current = current->GetNext();
			if (current == NULL)
			{
				InserеtInTail(x);
				return;
			}
		}
		
		current->GetPrevious()->SetNext(temp);
		temp->SetPrevious(current->GetPrevious());
		temp->SetNext(current);
		current->SetPrevious(temp);

		length++;
	}

	Type operator[](int n)
	{
		Node<Type>* temp = Search(n);
		return temp->GetVar();
	}

	void DeleteFirst() {
		if (length == 0) return;

		Node<Type> *temp = head;
		head = temp->GetNext();
		if (head != NULL) {
			head->SetPrevious(NULL);
		}
		delete temp;
		length--;
	}

	void Delete() {
		while (length != 0) {
			DeleteFirst();
		}
		//head = NULL;
	}


	void DeleteElement(int pos) //по позиции
	{
		
		Node<Type>* current = Search(pos);
		current->GetPrevious()->SetNext(current->GetNext());
		current->GetNext()->SetPrevious(current->GetPrevious());
		delete current;
		length--;
	};

	~List() {
		Delete();
	}

};

