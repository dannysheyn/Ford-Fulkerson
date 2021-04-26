#include <iostream>
#include "Graph.h"
#include "Edge.h"
#include "Node.h"

using namespace std;
class Node;
class Edge;

Graph::Graph(int i_NumberOfNodes)
{
	m_NumberOfNodes = i_NumberOfNodes;
	MakeEmptyGraph(i_NumberOfNodes);
}

void Graph::AddAntiParallelism()
{
	for (int i = 0; i < m_NumberOfNodes; i++)
	{
		for (int j = 0; j < m_NumberOfNodes; j++)
		{
			if (m_Graph[i][j].IsEdge() == true && m_Graph[j][i].IsEdge() == false)
			{
				AddEdge(j, i, 0);
			}
		}
	}
}

bool Graph::IsInRange(int i_Vertex)
{
	return (i_Vertex >= 0 && i_Vertex < m_NumberOfNodes);
}

Graph::Graph(Edge ** i_Graph, int i_Size)
{
	m_Graph = i_Graph;

	for (int i = 0; i < i_Size; i++)
	{
		m_Graph[i] = new Edge[i_Size];
	}

	m_NumberOfNodes = i_Size;
}

void Graph::PrintGraph()
{
	for (int i = 0; i < m_NumberOfNodes; i++)
	{
		cout << i << ": ";
		for (int j = 0; j < m_NumberOfNodes; j++)
		{
			cout << m_Graph[i][j].GetCurrentFlow() << "/" << m_Graph[i][j].GetCapacity() << " ";
		}

		cout << endl;
	}
}

void Graph::MakeEmptyGraph(int i_NumberOfNodes)
{
	m_Graph = new Edge*[i_NumberOfNodes];
	AllocationTest(m_Graph);

	for (int i = 0; i < i_NumberOfNodes; i++) 
	{
		m_Graph[i] = new Edge[i_NumberOfNodes];
		AllocationTest(m_Graph[i]);
	}
}

void Graph::AllocationTest(void * ptr)
{
	Node::AllocationTest(ptr);
}

bool Graph::IsAdjacent(int i_Source, int i_Destination)
{
	if (IsInRange(i_Source) == true && IsInRange(i_Destination) == true)
	{
		return m_Graph[i_Source][i_Destination].IsEdge();
	}
	else
	{
		throw new exception("Invalid prameters were given\n");
	}
}

LinkedList* Graph::GetAdjList(int i_Source)
{
	if (IsInRange(i_Source) == true)
	{
		LinkedList* linkedList = new LinkedList;
		AllocationTest(linkedList);

		for (int i = 0; i < m_NumberOfNodes; i++)
		{
			if (m_Graph[i_Source][i].IsEdge() == true)
			{
				linkedList->AddToTail(i);
			}
		}

		return linkedList;
	}
	else
	{
		throw new exception("Invalid prameters were given\n");
	}
}

LinkedList * Graph::GetAdjListResidual(int i_Source)
{
	if (IsInRange(i_Source) == true)
	{
		LinkedList* linkedList = new LinkedList;
		AllocationTest(linkedList);

		for (int i = 0; i < m_NumberOfNodes; i++)
		{
			if (m_Graph[i_Source][i].GetResidualFlow() != 0 && m_Graph[i_Source][i].IsEdge() == true)
			{
				linkedList->AddToTail(i);
			}
		}

		return linkedList;
	}
	else
	{
		throw new exception("Invalid prameters were given\n");
	}
}

void Graph::StartOver()
{
	for (int i = 0; i < m_NumberOfNodes; i++)
	{
		for (int j = 0; j < m_NumberOfNodes; j++)
		{
			m_Graph[i][j].SetCurrentFlow(0);
		}
	}
}

void Graph::AddEdge(int i_Source, int i_Destination, int i_Capacity)
{
	if (IsInRange(i_Source) == true && IsInRange(i_Destination) == true)
	{
		m_Graph[i_Source][i_Destination].m_Capacity = i_Capacity;
		m_Graph[i_Source][i_Destination].m_ResidualFlow = i_Capacity;
		m_Graph[i_Source][i_Destination].SetEdge(true);
	}
	else
	{
		throw new exception("Invalid prameters were given\n");
	}
}

void Graph::RemoveEdge(int i_Source, int i_Destination)
{
	if (IsInRange(i_Source) == true && IsInRange(i_Destination) == true)
	{
		m_Graph[i_Source][i_Destination].m_Capacity = 0;
		m_Graph[i_Source][i_Destination].SetEdge(false);
		m_Graph[i_Source][i_Destination].SetCurrentFlow(0);
	}
	else
	{
		throw new exception("Invalid prameters were given\n");
	}
}

Edge Graph::GetEdge(int i_Source, int i_Destination)
{
	if (IsInRange(i_Source) == true && IsInRange(i_Destination) == true)
	{
		return m_Graph[i_Source][i_Destination];
	}
	else
	{
		throw new exception("Invalid prameters were given\n");
	}
}

int Graph::GetCurrentFlow(int i_Source, int i_Destination)
{
	if (IsInRange(i_Source) == true && IsInRange(i_Destination) == true)
	{
		return m_Graph[i_Source][i_Destination].GetCurrentFlow();
	}
	else
	{
		throw new exception("Invalid prameters were given\n");
	}
}

int Graph::GetResidualFlow(int i_Source, int i_Destination)
{
	if (IsInRange(i_Source) == true && IsInRange(i_Destination) == true)
	{
		return m_Graph[i_Source][i_Destination].GetResidualFlow();
	}
	else
	{
		throw new exception("Invalid prameters were given\n");
	}
}

void Graph::SetCurrentFlow(int i_Source, int i_Destination, int i_ResidualFlow)
{
	if (IsInRange(i_Source) == true && IsInRange(i_Destination) == true)
	{
		m_Graph[i_Source][i_Destination].SetCurrentFlow(i_ResidualFlow);
	}
	else
	{
		throw new exception("Invalid prameters were given\n");
	}
}

void Graph::MakeEmpty()
{
	int num = m_NumberOfNodes;

	for (int i = 0; i < num; i++)
	{
		delete[] m_Graph[i];
	}

	delete[] m_Graph;
}

Graph::~Graph()
{
	MakeEmpty();
}

int Graph::GetNumberOfNodes()
{
	return m_NumberOfNodes;
}
