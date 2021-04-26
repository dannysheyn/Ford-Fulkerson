#include "Element.h"
#include "MaxHeap.h"
#include "Node.h"
#include <iostream>

using namespace std;
class Node;

void MaxHeap::MakeEmpty()
{
	if (m_Allocated == 1)
	{
		delete[] m_ElemntArr;
	}

	delete[] m_IsStillinQueue;
	delete[] m_PlaceElementInQueue;
	m_ElemntArr = nullptr;
}

bool MaxHeap::IsQueueEmpty()
{
	return (m_HeapSize < 1);
}

bool MaxHeap::IsEmpty()
{
	return m_ElemntArr == nullptr;
}

void MaxHeap::Insert(Element i_NewElement)
{
	if (m_HeapSize == m_MaxSize) 
	{
		cout << "overflow: Could not insert\n";
		return;
	}

	int i = m_HeapSize;
	m_HeapSize++;

	while (i > 0 && m_ElemntArr[parent(i)].GetKey() < i_NewElement.GetKey())
	{
		m_ElemntArr[i] = m_ElemntArr[parent(i)];
		i = parent(i); 
	}
	m_IsStillinQueue[i] = true;
	m_ElemntArr[i] = i_NewElement;
	m_PlaceElementInQueue[m_ElemntArr[i].GetData()] = i;
}

Element MaxHeap::DeleteMax()
{
	if (m_HeapSize < 1)
	{
		cout << "Eror: EMPTY HEAP\n";
	}

	Element max = m_ElemntArr[0];
	m_IsStillinQueue[max.GetData()] = false;
	m_HeapSize--;
	m_ElemntArr[0].SetData(m_ElemntArr[m_HeapSize].GetData());
	m_ElemntArr[0].SetKey(m_ElemntArr[m_HeapSize].GetKey());

	m_PlaceElementInQueue[m_ElemntArr[m_HeapSize].GetData()] = 0;

	FixHeap(0);

	return max;
}

void MaxHeap::BuildHeap()
{
	for (int i = m_HeapSize / 2 - 1; i >= 0; i--)
		FixHeap(i);
}

void MaxHeap::IncreaseKey(int i_Place, int i_NewKey)
{
	int place = m_PlaceElementInQueue[i_Place];

	m_ElemntArr[place].SetKey(i_NewKey);

	while (m_ElemntArr[place].GetKey() > m_ElemntArr[parent(place)].GetKey())
	{
		m_PlaceElementInQueue[m_ElemntArr[place].GetData()] = parent(place);
		m_PlaceElementInQueue[m_ElemntArr[parent(place)].GetData()] = place;
		std::swap(m_ElemntArr[place], m_ElemntArr[parent(place)]);
		place = parent(place);
	}
}

int MaxHeap::Find(int i_Place)
{
	for (int i = 0; i < m_HeapSize; i++)
	{
		if (m_ElemntArr[i].GetData() == i_Place)
		{
			return i;
		}
	}

	return -1; // not found
}

void MaxHeap::PrintQueque() 
{
	for (int i = 0; i < m_HeapSize; i++)
	{
		cout << " " << m_ElemntArr[i].GetKey() << "/" << m_ElemntArr[i].GetData();
	}

	cout << endl;

	for (int i = 0; i < m_HeapSize; i++)
	{
		cout << i << " cell: " << m_PlaceElementInQueue[i] << " ";
	}
	cout << endl;
}

Element* MaxHeap::Max()
{
	if (IsEmpty() == false)
	{
		return &m_ElemntArr[0];
	}
	else
	{
		return nullptr;
	}
}

bool MaxHeap::IsElementInQueue(int i_Vertex)
{
	return m_IsStillinQueue[i_Vertex];
}

MaxHeap::MaxHeap(Element* i_Arr, int i_Size)
{
	m_HeapSize = m_MaxSize = i_Size;
	m_PlaceElementInQueue = new int[i_Size];
	m_IsStillinQueue = new bool[i_Size];
	m_ElemntArr = i_Arr;
	m_Allocated = 0;
	m_PlaceElemntSize = i_Size;

	for (int i = 0; i < i_Size; i++)
	{
		m_IsStillinQueue[i] = true;
		m_PlaceElementInQueue[i] = i;
	}

	for (int i = i_Size / 2 - 1; i >= 0; i--)
		FixHeap(i);
}

MaxHeap::MaxHeap(int i_Max)
{
	m_ElemntArr = new Element[i_Max];
	m_PlaceElementInQueue = new int[i_Max];
	Node::AllocationTest(m_ElemntArr);
	m_IsStillinQueue = new bool[i_Max];
	m_MaxSize = i_Max;
	m_PlaceElemntSize = i_Max;
	m_HeapSize = 0;
	m_Allocated = 1;
}

MaxHeap::~MaxHeap()
{
	MakeEmpty();
}

void MaxHeap::FixHeap(int i_Node)
{
	int max;
	int left = getLeft(i_Node);
	int right = getRight(i_Node);

	if (left < m_HeapSize && (m_ElemntArr[left].GetKey() > m_ElemntArr[i_Node].GetKey()))
	{
		max = left;
	}
	else
	{
		max = i_Node;
	}

	if ((right < m_HeapSize) && (m_ElemntArr[right].GetKey() > m_ElemntArr[max].GetKey()))
	{
		max = right;
	}

	if (max != i_Node)
	{
		std::swap(m_ElemntArr[i_Node], m_ElemntArr[max]);
		m_PlaceElementInQueue[m_ElemntArr[i_Node].GetData()] = i_Node;
		m_PlaceElementInQueue[m_ElemntArr[max].GetData()] = max;

		FixHeap(max);
	}
}
