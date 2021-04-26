#include "Element.h"

Element::Element(int i_Data, int i_Key)
{
	m_Data = i_Data;
	m_Key = i_Key;
}

void Element::SetKey(int i_Key)
{
	m_Key = i_Key;
}

void Element::SetData(int i_Data)
{
	m_Data = i_Data;
}

int Element::GetData()
{
	return m_Data;
}

int Element::GetKey()
{
	return m_Key;
}
