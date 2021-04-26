#include "Node.h"
#include <iostream>

Node::Node(int i_Value, Node * i_NextNode)
{
	this->m_Value = i_Value;
	this->m_Next = i_NextNode;
}

Node::Node(int i_Value)
{
	this->m_Value = i_Value;
	this->m_Next = nullptr;
}

void Node::AllocationTest(void * ptr)
{
	if (!ptr)
	{
		std::cout << "Allocation error\n";
		exit(1);
	}
}

void Node::InsertAfter(Node * i_NextNode)
{
	Node* temp = this->m_Next;
	this->m_Next = i_NextNode;
	i_NextNode = temp;
}

Node * Node::DeleteAfter()
{
	Node* temp = this->m_Next;

	if (temp == nullptr)
	{
		return nullptr;
	}

	this->m_Next = temp->m_Next;

	return temp;
}

int Node::GetValue()
{
	return m_Value;
}
