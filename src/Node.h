#ifndef __NODE_H
#define __NODE_H


class Node
{
public:
	Node(int i_Value = 0, Node* i_NextNode = nullptr);
	Node(int i_Value);

	static void AllocationTest(void* ptr);

	void InsertAfter(Node* i_NextNode);
	Node* DeleteAfter();

	int GetValue();
	Node* m_Next;

private:
	int m_Value;
};

#endif // !__NODE_H