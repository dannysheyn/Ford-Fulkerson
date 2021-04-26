#ifndef __HEAP_H
#define __HEAP_H

class Element;

class MaxHeap
{
public:
	void MakeEmpty();
	bool IsQueueEmpty();
	bool IsEmpty();
	void Insert(Element i_NewElement);
	Element DeleteMax();
	Element* Max();
	bool IsElementInQueue(int i_Vertex);
	void BuildHeap();
	void IncreaseKey(int i_Place, int i_NewKey);
	int Find(int i_Place);

	void PrintQueque();

	MaxHeap(Element *arr, int size);
	MaxHeap(int max);
	~MaxHeap();
private:
	bool* m_IsStillinQueue;
	int* m_PlaceElementInQueue; //  m_PlaceElementInQueue[i] = place of data i
	int m_PlaceElemntSize;
	Element* m_ElemntArr;
	int m_MaxSize;
	int m_HeapSize;
	int m_Allocated;
	int parent(int i) { return (i - 1) / 2; }
	int getLeft(int i) { return (2 * i + 1); }
	int getRight(int i) { return (2 * i + 2); }
	void FixHeap(int node);
};

#endif // !__HEAP_H