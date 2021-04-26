#ifndef __GRAPH_H
#define __GRAPH_H
#include "LinkedList.h"
#include <iostream>

class Edge;


class Graph
{
public:
	Graph(Edge** i_Graph, int i_Size);
	Graph(int i_NumberOfNodes);

	void AddAntiParallelism();
	bool IsInRange(int i_Vertex);
	void PrintGraph();
	void MakeEmptyGraph(int i_NumberOfNodes);
	bool IsAdjacent(int i_Source,int i_Destination);
	LinkedList* GetAdjList(int i_Source);
	LinkedList* GetAdjListResidual(int i_Source);
	void StartOver();
	void AddEdge(int i_Source,int i_Destination,int i_Capacity);
	void RemoveEdge(int i_Source,int i_Destination);
	Edge GetEdge(int i_Source, int i_Destination);
	int GetCurrentFlow(int i_Souce, int i_Destination);
	int GetResidualFlow(int i_Souce, int i_Destination);
	void SetCurrentFlow(int i_Souce, int i_Destination, int i_ResidualFlow);
	void MakeEmpty();
	int GetNumberOfNodes();

	~Graph();

private:
	Edge** m_Graph;
	int m_NumberOfNodes;
	void AllocationTest(void * ptr);
};

#endif // !__GRAPH_H