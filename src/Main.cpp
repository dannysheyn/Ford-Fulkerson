/*
This program solves the Maximun flow problem, using Ford - Fulkerson methods, using both BFS (Edmonds - Karp Algorithm) 
and a greedy approach to find the improving route.

In order to create your own flow function and solve the Maximum flow program you need to follow these instructions:
	1. Create a simple text file called 'input.txt' and place it in the Solution's directory.
	2. First line of the text file should be the number of Vertexes in the graph (n).
	3. Second line of the text file should be the number of Edges in the graph (m).
	4. Third line of the text file should be the source vertex number (S).
	5. Forth line of the text file should be the destenation vertex number (T).
	6. m (number of Edges) lines - each line represents an edge in the graph.
	   The data in each line should be the source vertex, destenation vertex, and the edge's capacity,
	   in this format - source destenation capacity (emphasis on spaces).

All the edge's capacity values must be positive.
If any input will be invalid the program will notify the user before exiting

The program will retrieves all the data from the given file and build the graph using a matrix.
Then it will run both algorithm to solve the Maximum Flow problem.
For each run the program will print the Maximum Flow that was found, the Minimun cut and the number of iterations.
*/

#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "Node.h"
#include "Edge.h"
#include "Queue.h"
#include "Graph.h"
#include "MaxHeap.h"
#include "Element.h"
#include "InputChecker.h"

#define INFINITY INT_MAX

#pragma warning(disable: 4996)
using namespace std;

void AllocationTest(void* ptr);
Graph* ReadFromFile(string file_name, int* o_SourceNode, int* o_DestinationNode);
bool DIJKSTRA(Graph* G, int i_VertexS, int i_VertexT, int* i_ResidualWeight, int* i_ParentArr);
bool BFS(Graph* G, int i_VertexS, int i_VertexT, int* i_DistanceArr, int* i_ParentArr);
string FindMinCut(Graph* G, int i_Vertex, int i_VertexT, int* i_DistanceArr, int* i_ParentArr);
int FORD_FULKERSON_BFS(Graph* G, int i_Source, int i_Destination, int* i_DistanceArr, int* i_ParentArr, int* o_IterationCount);
int FORD_FULKERSON_DIJKSTRA(Graph* G, int i_Source, int i_Destination, int* i_DistanceArr, int* i_ParentArr, int* o_IterationCount);

int main(int argc, char* argv[])
{
	string filePath = "input1.txt";
	InputChecker::ValidateFormat(filePath);
	int vertexS, vertexT, maxFlow, numberOfiterations = 0;
	Graph *graph = ReadFromFile(filePath, &vertexS, &vertexT);
	string minCut;

	graph->AddAntiParallelism();
	int numOfVertexes = graph->GetNumberOfNodes();
	int* distanceArr = new int[numOfVertexes];
	AllocationTest(distanceArr);
	int* parentArr = new int[numOfVertexes];
	AllocationTest(parentArr);

	maxFlow = FORD_FULKERSON_BFS(graph, vertexS - 1, vertexT - 1, distanceArr, parentArr, &numberOfiterations);
	minCut = FindMinCut(graph, vertexS - 1, vertexT - 1, distanceArr, parentArr);
	cout << "BFS Method:" << endl;
	cout << "Max flow = " << maxFlow << endl << "Min cut: " << minCut << endl << "Number of iterations = " << numberOfiterations << endl;

	graph->StartOver();

	numberOfiterations = 0;
	maxFlow = FORD_FULKERSON_DIJKSTRA(graph, vertexS - 1, vertexT - 1, distanceArr, parentArr, &numberOfiterations);
	minCut = FindMinCut(graph, vertexS - 1, vertexT - 1, distanceArr, parentArr);

	cout << "Greedy Method:" << endl;
	cout << "Max flow = " << maxFlow << endl << "Min cut: " << minCut << endl << "Number of iterations = " << numberOfiterations << endl;

	delete[] distanceArr;
	delete[] parentArr;
	delete graph;
	return 0;
}

bool ValidateEdge(int i_NumberOfVertexes, int i_Source, int i_Destination, int i_Capacity)
{
	if (i_Source > i_NumberOfVertexes || i_Source <= 0)
	{
		return false;
	}

	if (i_Destination > i_NumberOfVertexes || i_Destination <= 0)
	{
		return false;
	}

	if (i_Capacity <= 0)
	{
		return false;
	}

	if (i_Destination == i_Source)
	{
		return false;
	}

	return true;
}

Graph* ReadFromFile(string file_name, int* o_SourceNode, int* o_DestinationNode)
{
	int sourceNode, destinationNode, vertexCapacity;
	ifstream in_file;
	in_file.open(file_name, ios::in);
	string numberOfVertexesStr, numberOfEgeds, vertexS, vertexT;
	int numberOfVertexes;

	getline(in_file, numberOfVertexesStr);
	getline(in_file, numberOfEgeds);
	getline(in_file, vertexS);
	getline(in_file, vertexT);

	int edgeNum = stoi(numberOfEgeds);
	numberOfVertexes = stoi(numberOfVertexesStr);
	Graph* graph = new Graph(numberOfVertexes);
	AllocationTest(graph);

	*o_SourceNode = stoi(vertexS);
	*o_DestinationNode = stoi(vertexT);

	for (int i = 0; i < edgeNum; i++)
	{
		in_file >> sourceNode;
		in_file >> destinationNode;
		in_file >> vertexCapacity;

		if (ValidateEdge(numberOfVertexes, sourceNode, destinationNode, vertexCapacity) == false || graph->GetEdge(sourceNode - 1, destinationNode - 1).IsEdge() == true)
		{
			cout << "Invalid input!" << endl;
			exit(1);
		}

		graph->AddEdge(sourceNode - 1, destinationNode - 1, vertexCapacity);
	}

	in_file.close();
	return graph;
}

void AllocationTest(void* ptr)
{
	Node::AllocationTest(ptr);
}

string FindMinCut(Graph* G, int i_Vertex, int i_VertexT, int* i_DistanceArr, int* i_ParentArr)
{
	string S_Cut = "S =";
	string T_Cut = "T =";

	int numOfVertices = G->GetNumberOfNodes();
	BFS(G, i_Vertex, i_VertexT, i_DistanceArr, i_ParentArr);

	for (int i = 0; i < numOfVertices; i++)
	{
		if (i_DistanceArr[i] != INFINITY)
		{
			S_Cut += " ";
			S_Cut += to_string(i + 1);
			S_Cut += ",";
		}
		else
		{
			T_Cut += " ";
			T_Cut += to_string(i + 1);
			T_Cut += ",";
		}
	}

	S_Cut.pop_back();
	S_Cut += ". ";

	T_Cut.pop_back();
	T_Cut += ".";

	S_Cut += T_Cut;
	return S_Cut;
}

void InitializeSingleSource(int i_Size, int i_Vertex, int* i_DistanceArr, int* i_ParentArr, Element* i_ElementArr)
{
	for (int i = 0; i < i_Size; i++)
	{
		i_ElementArr[i].SetData(i);
		i_ElementArr[i].SetKey(0);
		i_DistanceArr[i] = 0;
		i_ParentArr[i] = INFINITY;
	}

	i_ElementArr[i_Vertex].SetKey(INFINITY);
	i_DistanceArr[i_Vertex] = INFINITY;
	i_ParentArr[i_Vertex] = 0;
}

int Min(int i_left, int i_Right)
{
	return i_left < i_Right ? i_left : i_Right;
}

bool IsImprovingPath(int i_Source, int i_Destination, int* i_ParentArr)
{
	int currentVertex = i_Destination;

	while (currentVertex != i_Source)
	{
		if (i_ParentArr[currentVertex] != INFINITY)
		{
			currentVertex = i_ParentArr[currentVertex];
		}
		else
		{
			return false;
		}
	}

	if (i_Source == i_Destination)
	{
		return false;
	}

	return true;
}

void Relax(Graph* G, int i_Source, int i_Destination, int* i_ResidualWeight, int* i_ParentArr, MaxHeap* Q)
{
	if (Q->IsElementInQueue(i_Destination) == true)
	{
		if (i_ResidualWeight[i_Destination] < Min(G->GetEdge(i_Source, i_Destination).GetResidualFlow(), i_ResidualWeight[i_Source]))
		{
			i_ResidualWeight[i_Destination] = Min(G->GetEdge(i_Source, i_Destination).GetResidualFlow(), i_ResidualWeight[i_Source]);
			i_ParentArr[i_Destination] = i_Source;
			Q->IncreaseKey(i_Destination, i_ResidualWeight[i_Destination]);
		}
	}
}

bool DIJKSTRA(Graph* G, int i_VertexS, int i_VertexT, int* i_ResidualWeight, int* i_ParentArr)
{
	int numberOfNodes = G->GetNumberOfNodes();
	Element* elementArr = new Element[numberOfNodes];
	Element currentVertex;
	LinkedList* neighborsLists;
	Node* listHead;

	InitializeSingleSource(numberOfNodes, i_VertexS, i_ResidualWeight, i_ParentArr, elementArr);
	MaxHeap* queue = new MaxHeap(elementArr, numberOfNodes);
	AllocationTest(queue);

	while (queue->IsQueueEmpty() == false)
	{
		currentVertex = queue->DeleteMax();
		neighborsLists = G->GetAdjListResidual(currentVertex.GetData());
		listHead = neighborsLists->getHead();

		while (listHead != nullptr)
		{
			Relax(G, currentVertex.GetData(), listHead->GetValue(), i_ResidualWeight, i_ParentArr, queue);
			listHead = listHead->m_Next;
		}

		delete neighborsLists;
	}

	delete elementArr;
	delete queue;
	return IsImprovingPath(i_VertexS, i_VertexT, i_ParentArr);
}

int FORD_FULKERSON_DIJKSTRA(Graph* G, int i_Source, int i_Destination, int* i_ResidualWeight, int* i_ParentArr, int* o_IterationCount)
{
	int maxFlow = 0;
	int minEdge;
	int currentVertex;
	int currentNodeValue, nextNodeValue;
	LinkedList improvingPath;
	Node* currentNode;
	Node* nextNode;
	Edge tempEdge;

	while (DIJKSTRA(G, i_Source, i_Destination, i_ResidualWeight, i_ParentArr) == true)
	{
		currentVertex = i_Destination;
		minEdge = i_ResidualWeight[i_Destination];
		improvingPath.AddToHead(currentVertex);

		while (currentVertex != i_Source) // find Cf(P) 
		{
			currentVertex = i_ParentArr[currentVertex];
			improvingPath.AddToHead(currentVertex);
		}

		currentNode = improvingPath.getHead();

		while (currentNode->m_Next != nullptr)
		{
			nextNode = currentNode->m_Next;

			currentNodeValue = currentNode->GetValue();
			nextNodeValue = nextNode->GetValue();

			tempEdge.SetCurrentFlow(G->GetCurrentFlow(currentNodeValue, nextNodeValue)); // update the flow in G

			tempEdge.SetCurrentFlow(tempEdge.GetCurrentFlow() + minEdge);                                   // f(u, v) <- f(u, v) + Cf(P) | P = improving path
			G->SetCurrentFlow(currentNodeValue, nextNodeValue, tempEdge.GetCurrentFlow());                  // Cf(u, v) <- Cf(u, v) - f(u, v) | f(u, v) = current flow
																											// update the residual flow  
			G->SetCurrentFlow(nextNodeValue, currentNodeValue, tempEdge.GetCurrentFlow() * -1);             // f(v, u) <- -f(u, v)     
																											// Cf(v, u) <- Cf(v, u) - f(v, u) | f(v, u) = current flow
			currentNode = currentNode->m_Next;
		}

		(*o_IterationCount)++;
		improvingPath.MakeEmpty();
		maxFlow += minEdge;
	}

	return maxFlow;
}

void InitializeBFS(int i_Size, int i_Vertex, int* i_DistanceArr, int* i_ParentArr)
{
	for (int i = 0; i < i_Size; i++)
	{
		i_DistanceArr[i] = INFINITY;
		i_ParentArr[i] = INFINITY;
	}

	i_DistanceArr[i_Vertex] = 0;
	i_ParentArr[i_Vertex] = 0;
}

bool BFS(Graph* G, int i_VertexS, int i_VertexT, int* i_DistanceArr, int* i_ParentArr)
{
	Queue queue;
	LinkedList* neighborsLists;
	Node* listHead;
	int currentVertex;
	int currentNeighbour;
	int count = 1;
	int numberOfNodes = G->GetNumberOfNodes();

	InitializeBFS(numberOfNodes, i_VertexS, i_DistanceArr, i_ParentArr);

	queue.EnQueue(i_VertexS);

	while (queue.IsEmpty() == false)
	{
		currentVertex = queue.DeQueue();
		neighborsLists = G->GetAdjListResidual(currentVertex);
		listHead = neighborsLists->getHead();

		while (listHead != nullptr)
		{
			currentNeighbour = listHead->GetValue();

			if (i_DistanceArr[currentNeighbour] == INFINITY)
			{
				i_DistanceArr[currentNeighbour] = i_DistanceArr[currentVertex] + 1;
				i_ParentArr[currentNeighbour] = currentVertex;
				queue.EnQueue(currentNeighbour);
			}

			listHead = listHead->m_Next;
		}

		delete neighborsLists;
	}

	return IsImprovingPath(i_VertexS, i_VertexT, i_ParentArr);
}

int FORD_FULKERSON_BFS(Graph* G, int i_Source, int i_Destination, int* i_DistanceArr, int* i_ParentArr, int* o_IterationCount)
{
	int maxFlow = 0;
	int minEdge;
	int currentVertex;
	LinkedList improvingPath;
	Node* currentNode;
	Node* nextNode;
	Edge tempEdge;

	while (BFS(G, i_Source, i_Destination, i_DistanceArr, i_ParentArr) == true)
	{
		currentVertex = i_Destination;

		minEdge = G->GetResidualFlow(i_ParentArr[currentVertex], currentVertex);
		improvingPath.AddToHead(currentVertex);

		while (currentVertex != i_Source)  // find Cf(P) 
		{
			if (G->GetResidualFlow(i_ParentArr[currentVertex], currentVertex) < minEdge)
			{
				minEdge = G->GetResidualFlow(i_ParentArr[currentVertex], currentVertex);
			}

			currentVertex = i_ParentArr[currentVertex];
			improvingPath.AddToHead(currentVertex);
		}

		currentNode = improvingPath.getHead();

		while (currentNode->m_Next != nullptr)
		{
			nextNode = currentNode->m_Next;

			tempEdge.SetCurrentFlow(G->GetCurrentFlow(currentNode->GetValue(), nextNode->GetValue())); // update the flow in G
			tempEdge.SetCurrentFlow(tempEdge.GetCurrentFlow() + minEdge);                                           // f(u, v) <- f(u, v) + Cf(P) | P = improving path
			G->SetCurrentFlow(currentNode->GetValue(), nextNode->GetValue(), tempEdge.GetCurrentFlow());            // Cf(u, v) <- Cf(u, v) - f(u, v) | f(u, v) = current flow
																													// update the residual flow  
			G->SetCurrentFlow(nextNode->GetValue(), currentNode->GetValue(), tempEdge.GetCurrentFlow() * -1);       // f(v, u) <- -f(u, v)     
																													// Cf(v, u) <- Cf(v, u) - f(v, u) | f(v, u) = current flow
			currentNode = currentNode->m_Next;
		}

		(*o_IterationCount)++;
		improvingPath.MakeEmpty();
		maxFlow += minEdge;
	}

	return maxFlow;
}
