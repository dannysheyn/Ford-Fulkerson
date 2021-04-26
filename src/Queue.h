#ifndef __QUEUE_H
#define __QUEUE_H

class Node;

class Queue
{
public:

	void MakeEmpty();
	bool IsEmpty();
	int Front();
	int DeQueue();
	void EnQueue(int i_Value);

	Node* GetHead();
	Node* GetTail();
	int GetSize();

	Queue();
	~Queue();
private:
	Node* m_Head;
	Node* m_Tail;
	int m_Size = 0;
};
#endif // !__QUEUE_H
