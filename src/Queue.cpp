#include "Node.h"
#include "Queue.h"
#include <iostream>
using namespace std;

void Queue::MakeEmpty()
{
	Node* temp;

	while (m_Head != nullptr)
	{
		temp = m_Head->m_Next;
		delete m_Head;
		m_Head = temp;
	}
}

bool Queue::IsEmpty()
{
	return m_Head == m_Tail;
}

int Queue::Front()
{
	if (IsEmpty() == true)
	{
		cout << "Error: QUEUE EMPTY\n";
		exit(1);
	}

	return m_Head->m_Next->GetValue();
}

int Queue::DeQueue()
{
	if (IsEmpty() == true)
	{
		cout << "Error: QUEUE EMPTY\n";
		exit(1);
	}

	Node* temp = m_Head->DeleteAfter();
	int item = temp->GetValue();

	if (m_Tail == temp)
	{
		m_Tail = m_Head;
	}

	m_Size--;
	delete temp;
	return item;
}

void Queue::EnQueue(int i_Value)
{
	Node* newNode = new Node(i_Value, nullptr);
	Node::AllocationTest(newNode);
	m_Tail->InsertAfter(newNode);
	m_Tail = newNode;
	m_Size++;
}

Node * Queue::GetHead()
{
	return m_Head;
}

Node * Queue::GetTail()
{
	return m_Tail;
}

int Queue::GetSize()
{
	return m_Size;
}

Queue::Queue()
{
	m_Head = new Node;
	Node::AllocationTest(m_Head);
	m_Tail = m_Head;
	m_Size = 0;
}

Queue::~Queue()
{
	MakeEmpty();
}
