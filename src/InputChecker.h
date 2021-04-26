#ifndef __INPUTCHECKER_H
#define __INPUTCHECKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;
#pragma warning(disable: 4996)

class InputChecker
{
public:
	static void ValidateFormat(string i_FileName);

private:
	static bool IsDigit(char i_Ch);
	static bool ValidateData(string i_DataString);
	static bool ValidateInitialStrings(string i_NumberOfVertexesStr, string i_NumberOfEgeds, string i_VertexS, string i_VertexT);
	static bool ValidateEdgeFormat(string i_EdgeString);
	static bool FileExists(const char * name);

	enum eStateValidate
	{
		NoIntFound,
		NumInProgress,
		FoundNum
	};
};
#endif // !__INPUTCHECKER_H