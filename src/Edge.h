#ifndef __EDGE_H
#define __EDGE_H


class Edge
{
public:
	friend class Graph;

	Edge(int i_Capacity = 0);

	void SetEdge(bool i_IsEdge);
	void SetCurrentFlow(int i_CurrentFlow);

	int GetCapacity();
	int GetCurrentFlow();
	int GetResidualFlow();
	bool IsEdge();

private:
	int m_Capacity;
	int m_CurrentFlow;
	int m_ResidualFlow;
	bool m_IsEdge;
};

#endif // !__EDGE_H