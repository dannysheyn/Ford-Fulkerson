#include "Edge.h"

Edge::Edge(int i_Capacity) : m_Capacity(i_Capacity)
{
	m_ResidualFlow = i_Capacity;
	m_CurrentFlow = 0;
	m_IsEdge = false;
}

void Edge::SetEdge(bool i_IsEdge)
{
	m_IsEdge = i_IsEdge;
}

void Edge::SetCurrentFlow(int i_CurrentFlow)
{
	m_CurrentFlow = i_CurrentFlow;
	m_ResidualFlow = m_Capacity - m_CurrentFlow;
}

int Edge::GetCapacity()
{
	return m_Capacity;
}

int Edge::GetCurrentFlow()
{
	return m_CurrentFlow;
}

int Edge::GetResidualFlow()
{
	return m_ResidualFlow;
}

bool Edge::IsEdge()
{
	return m_IsEdge;
}
