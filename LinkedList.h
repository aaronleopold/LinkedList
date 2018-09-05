#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
	NOTE: All functions with return type Node will be defined inside the class brackets!
*/

template<class T>
class LinkedList
{
    public:
        class Node
        {
        public:
            T data;
            Node *next, *prev;

            Node() {next = nullptr; prev = nullptr; data = T();}
        };
        //=====Accessors=====//
        void PrintForward() const;
        void PrintReverse() const;
        unsigned int NodeCount() const;
        void FindAll(vector<Node *> &outData, const T &value) const;
		const Node *Find(const T &data) const
		{
			for (unsigned int i = 0; i < count; i++)
			{
				const Node *curr = GetNode(i);
				if (curr->data == data)
					return curr;
			}

			return nullptr;
		}

		Node *Find(const T &data)
		{
			for (unsigned int i = 0; i < count; i++)
			{
				Node *curr = GetNode(i);
				if (curr->data == data)
					return curr;
			}

			return nullptr;
		}

		const Node * GetNode(unsigned int index) const
		{
			const Node *current = head;
			for (unsigned int i = 0; i < count; i++)
			{
				if (i == index)
					return current;
				current = current->next;
			}

			return nullptr;
		}

		Node *GetNode(unsigned int index)
		{
			Node *current = head;
			for (unsigned int i = 0; i < count; i++)
			{
				if (i == index)
					return current;
				current = current->next;
			}

			return nullptr;
		}

		Node *Head() { return head; }
		const Node *Head() const { return head; }
		Node *Tail() { return tail; }
		const Node *Tail() const { return tail; }

        //=====Insertion=====//
        void AddHead(const T &data);
        void AddTail(const T &data);
        void AddNodesHead(const T *data, unsigned int count);
        void AddNodesTail(const T *data, unsigned int count);
        void InsertAfter(Node *node, const T &data);
        void InsertBefore(Node *node, const T &data);
        void InsertAt(const T &data, unsigned int index);

        //=====Removal=====//
        bool RemoveHead();
        bool RemoveTail();
        unsigned int Remove(const T &data);
        bool RemoveAt(int index);
        void Clear();

        //=====Operators=====//
        const T & operator[](unsigned int index) const;
        T & operator[](unsigned int index);
        bool operator==(const LinkedList<T> &rhs) const;
        LinkedList<T> & operator=(const LinkedList<T> &rhs);

        //=====Constructors / Destructor=====//
        LinkedList();
        LinkedList(const LinkedList<T> &list);
        ~LinkedList();

        //====Helper Functions====//
        void Set(const LinkedList<T> &other);

    private:
        Node *head, *tail;
        unsigned int count;
};

//=====Accessors=====//
template<class T>
void LinkedList<T>::PrintForward() const
{
    //catch empty list
    Node *current = head;
    while (current != nullptr)
    {
        cout << current->data << endl;
        current = current->next;
    }
}

template<class T>
void LinkedList<T>::PrintReverse() const
{
    //catch empty list
    Node *current = tail;
    while (current != nullptr)
    {
        cout << current->data << endl;
        current = current->prev;
    }
}

template <class T>
unsigned int LinkedList<T>::NodeCount() const
{
    return count;
}

template<class T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T &value) const
{
    Node *curr = head;
    for (unsigned int i = 0; i < count; i++)
    {
        if (curr->data == value)
            outData.push_back(curr);
        curr = curr->next;
    }
}

//=====Insertion=====//
template<class T>
void LinkedList<T>::AddHead(const T &data)
{
    Node *temp = new Node;
    temp->data = data;

    if (count == 0)
    {
        temp->next = nullptr;
        temp->prev = nullptr;
        head = temp;
        tail = temp;
    }
    else
    {
        temp->next = head;
        temp->prev = nullptr;
        head->prev = temp;
        head = temp;
    }

    count++;
}

template<class T>
void LinkedList<T>::AddTail(const T &data)
{
	if (count == 0)
		AddHead(data);
	else if (tail == head)
	{
		Node *temp = new Node;
		temp->data = data;
		temp->prev = head;
		temp->next = nullptr;
		head->next = temp;
		tail = temp;
		count++;
	}
	else
	{
		Node *temp = new Node;
		temp->data = data;
		temp->prev = tail;
		temp->next = nullptr;
		tail->next = temp;
		tail = temp;
		count++;
	}
}

template<class T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count)
{
	//add last first
	for (unsigned int i = count; i > 0; i--)
	{
		AddHead(data[i - 1]);
	}
}

template<class T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count)
{
	//add last first
	for (unsigned int i = 0; i < count; i++)
	{
		AddTail(data[i]);
	}

}

template<class T>
void LinkedList<T>::InsertAfter(Node *node, const T &data)
{
	for (unsigned int i = 0; i < count; i++)
	{
		Node *curr = GetNode(i);

		if (curr == node)
		{
			Node *temp = new Node;
			temp->data = data;
			temp->next = curr->next;
			temp->prev = curr;
			curr = curr->next;
			curr->prev = temp;
			curr = temp->prev;
			curr->next = temp;
			count++;
			break;
		}
	}
}

template<class T>
void LinkedList<T>::InsertBefore(Node *node, const T &data)
{
	for (unsigned int i = 0; i < count; i++)
	{
		Node *curr = GetNode(i);
		if (curr == node)
		{
			Node *temp = new Node;
			temp->data = data;
			temp->next = curr;
			temp->prev = curr->prev;
			curr = curr->prev;
			curr->next = temp;
			curr = temp->next;
			curr->prev = temp;
			count++;
			break;
		}
	}
}

template<class T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index)
{
	if (index > count)
		throw "Error!";
	else if (index == 0)
		AddHead(data);
	else if (index == count)
		AddTail(data);
	else
	{
		Node *curr = GetNode(index);
		Node *temp = new Node;
		temp->data = data;
		temp->next = curr;
		temp->prev = curr->prev;
		curr = curr->prev;
		curr->next = temp;
		curr = temp->next;
		curr->prev = temp;

		count++;
	}
}


//=====Removal=====//
template<class T>
bool LinkedList<T>::RemoveHead()
{
	if (count == 0)
		return false;
	if (count == 1)
    {
		delete head;
        head = nullptr;
        tail = nullptr;
        count--;
        return true;
    }

	Node *curr = head->next;
	curr->prev = nullptr;
	head->next = nullptr;
	delete head;
	head = curr;
	if (count == 2)
		tail = curr;

	count--;

	return true;
}

template<class T>
bool LinkedList<T>::RemoveTail()
{
	if (count == 0)
		return false;
    if (count == 1)
    {
		delete tail;
        head = nullptr;
        tail = nullptr;
        count--;
        return true;
    }

	Node *curr = tail->prev;
	curr->next = nullptr;
	tail->prev = nullptr;
	delete tail;
	tail = curr;

	count--;

	return true;
}

template <class T>
unsigned int LinkedList<T>::Remove(const T &data)
{
	unsigned int removedNodes = 0;

	for (unsigned int i = 0; i < count; i++)
	{
		Node *curr = GetNode(i);
		if (curr->data == data)
		{
			RemoveAt(i);
			removedNodes++;
			i--;
		}
	}

	return removedNodes;
}

template <class T>
bool LinkedList<T>::RemoveAt(int index)
{
	if ((unsigned)index > count || index < 0)
		return false;
	else if (head == nullptr)
		return false;
	else if (index == 0)
	{
		RemoveHead();
		return true;
	}
	else if ((unsigned)index == count)
	{
		RemoveTail();
		return true;
	}

	Node *target = GetNode(index);
	Node *curr1 = GetNode(index)->prev;
	Node *curr2 = GetNode(index)->next;
	curr1->next = curr2;
	curr2->prev = curr1;
	target->next = nullptr;
	target->prev = nullptr;
	delete target;
	count--;

	return true;
}

template<class T>
void LinkedList<T>::Clear()
{
	Node *curr1 = head;
	Node *curr2;
	while (curr1 != nullptr)
	{
		curr2 = curr1->next;
		curr1->next = nullptr;
		curr1->prev = nullptr;
		curr1->data = {};
		delete curr1;
		curr1 = curr2;
		count--;
	}

	head = nullptr;
	tail = nullptr;
}

//=====Operators=====//
template<class T>
const T & LinkedList<T>::operator[](unsigned int index) const
{
	if (index > count)
		throw "Error!";

	Node *curr = GetNode(index);

	return curr->data;
}

template<class T>
T & LinkedList<T>::operator[](unsigned int index)
{
	if (index > count)
		throw "Error!";

	Node *curr = GetNode(index);

	return curr->data;
}

template<class T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const
{
	if (this->count != rhs.count)
		return false;

    unsigned int matches = 0;
    for (unsigned int i = 0; i < count - 1; i++)
    {
       const Node *curr1 = GetNode(i);
       const Node *curr2 = rhs.GetNode(i);
        if (curr1->data == curr2->data)
            matches++;
    }

    if (matches == count - 1)
        return true;
    else
        return false;
}

template<class T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    Set(rhs);

    return *this;
}

//=====Constructors / Destructor=====//
template<class T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list)
{
    Set(list);
}

template<class T>
LinkedList<T>::~LinkedList()
{
	Clear();
	if (head != nullptr)
		delete head;
	if (tail != nullptr && tail != head)
		delete tail;
}

//====Helper Functions====//
template<class T>
void LinkedList<T>::Set(const LinkedList<T> &other)
{
	this->Clear();
	this->count = 0;

	const Node *curr = other.head;
	while (curr != nullptr)
	{
		this->AddTail(curr->data);
		curr = curr->next;
	}
}
