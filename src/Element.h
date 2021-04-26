#ifndef __ELEMENT_H
#define __ELEMENT_H


class Element
{
public:
	Element(int i_Data = 0, int i_Key = 0);

	void SetKey(int i_Key);

	void SetData(int i_Data);
	
	int GetData();
	int GetKey();

private:
	int m_Data;
	int m_Key;
};

#endif // !__ELEMENT_H