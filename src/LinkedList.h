#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

class Node;

class LinkedList
{
public:
	bool IsEmpty();
	void MakeEmpty();
	Node* Find(int i_Value);
	void DeleteNode(Node * i_NodeToDelete);
	void AddToTail(int i_Value);
	void AddToHead(int i_Value);

	void setHead(Node* head);
	void setTail(Node* tail);

	Node* getHead();
	Node* getTail();

	LinkedList(Node* i_Head = nullptr);
	~LinkedList();

private:
	int m_Size;
	Node* m_Head;
	Node* m_Tail;
};
#endif // !__LINKEDLIST_H
