#include "LinkedList.h"
#include "Node.h"

bool LinkedList::IsEmpty()
{
	if (m_Head == nullptr)
	{
		return true;
	}

	return false;
}

void LinkedList::MakeEmpty()
{
	Node* next = m_Head;
	Node* curr = nullptr;

	while (next != nullptr) 
	{
		curr = next;
		next = next->m_Next;
		delete curr;
	}

	m_Head = nullptr;
	m_Tail = nullptr;
	m_Size = 0;
}

Node * LinkedList::Find(int i_Value)
{
	Node* next = m_Head;
	Node* curr = nullptr;

	while (next != nullptr) 
	{
		if (next->GetValue() == i_Value)
		{
			break;
		}
		curr = next;
		next = next->m_Next;
	}

	return next;
}

void LinkedList::DeleteNode(Node * i_NodeToDelete)
{
	Node* next = m_Head;
	Node* curr = nullptr;

	while (next != nullptr) 
	{
		if (next == i_NodeToDelete)
		{
			break;
		}

		curr = next;
		next = next->m_Next;
	}

	curr->m_Next = next->m_Next;
	delete next;

	m_Size--;
}

void LinkedList::AddToTail(int i_Value)
{
	Node* newNode = new Node(i_Value, nullptr);
	Node::AllocationTest(newNode);

	if (m_Head == nullptr)
	{
		m_Head = newNode;
		m_Tail = newNode;
	}
	else
	{
		m_Tail->m_Next = newNode;
		newNode->m_Next = nullptr;
		m_Tail = newNode;
	}

	m_Size++;
}

void LinkedList::AddToHead(int i_Value)
{
	Node* newNode = new Node(i_Value, nullptr);
	Node::AllocationTest(newNode);

	if (m_Head == nullptr)
	{
		m_Head = newNode;
		m_Tail = newNode;
	}
	else
	{
		newNode->m_Next = m_Head;
		m_Head = newNode;
	}

	m_Size++;
}

void LinkedList::setHead(Node* head)
{
	m_Head = head;
}

void LinkedList::setTail(Node* tail)
{
	m_Tail = tail;
}

Node* LinkedList::getHead()
{
	return m_Head;
}

Node* LinkedList::getTail()
{
	return m_Tail;
}

LinkedList::LinkedList(Node* i_Head)
{
	setHead(i_Head);
	setTail(i_Head);
	m_Size = 0;
}

LinkedList::~LinkedList()
{
	MakeEmpty();
}