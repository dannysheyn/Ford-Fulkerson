#include "InputChecker.h"

bool InputChecker::IsDigit(char i_Ch)
{
	return ((i_Ch >= '0' && i_Ch <= '9'));
}

bool InputChecker::ValidateData(string i_DataString)
{
	int stringSize = i_DataString.size();
	eStateValidate state = NoIntFound;

	for (int i = 0; i < stringSize; i++)
	{
		if (IsDigit(i_DataString[i]))
		{
			if (state == NoIntFound)
			{
				state = NumInProgress;
			}
			else if (state == FoundNum)
			{
				return false;
			}
		}
		else if (i_DataString[i] == ' ' || i_DataString[i] == '\t')
		{
			if (state == NumInProgress)
			{
				state = FoundNum;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool InputChecker::ValidateInitialStrings(string i_NumberOfVertexesStr, string i_NumberOfEgeds, string i_VertexS, string i_VertexT)
{
	return (ValidateData(i_NumberOfVertexesStr) && ValidateData(i_NumberOfEgeds) && ValidateData(i_VertexS) && ValidateData(i_VertexT));
}

bool InputChecker::ValidateEdgeFormat(string i_EdgeString)
{
	int stringSize = i_EdgeString.size();
	eStateValidate state = NoIntFound;
	int count = 0;

	for (int i = 0; i < stringSize; i++)
	{
		if (IsDigit(i_EdgeString[i]))
		{
			if (state == NoIntFound)
			{
				state = NumInProgress;
			}

			if (count == 3)
			{
				return false;
			}
		}
		else if (i_EdgeString[i] == ' ' || i_EdgeString[i] == '\t')
		{
			if (state == NumInProgress)
			{
				if (count < 3)
				{
					state = NoIntFound;
				}
				else
				{
					return false;
				}

				count++;
			}
		}
		else
		{
			return false;
		}
	}

	return count == 3 || (count == 2 && state == NumInProgress);
}

bool InputChecker::FileExists(const char* name) 
{
	FILE *in_file = fopen(name, "r");

	if (in_file != nullptr)
	{
		fclose(in_file);
		return true;
	}
	else 
	{
		return false;
	}
}

void InputChecker::ValidateFormat(string i_FileName)
{
	ifstream in_file;

	if (FileExists(i_FileName.c_str()) == false)
	{
		cout << "File was not found\n";
		exit(1);
	}

	in_file.open(i_FileName, ios::in);
	string numberOfVertexesStr, numberOfEgeds, vertexS, vertexT, edgeInput;
	int numberOfVertexes;
	int numOfEdges;

	getline(in_file, numberOfVertexesStr);
	getline(in_file, numberOfEgeds);
	getline(in_file, vertexS);
	getline(in_file, vertexT);

	if (ValidateInitialStrings(numberOfVertexesStr, numberOfEgeds, vertexS, vertexT) == false)
	{
		cout << "Invalid format was given in the first 4 parameters\n.";
		exit(1);
	}

	numberOfVertexes = stoi(numberOfVertexesStr);
	numOfEdges = stoi(numberOfEgeds);

	for (int i = 0; i < numOfEdges; i++)
	{
		getline(in_file, edgeInput);

		if (ValidateEdgeFormat(edgeInput) == false)
		{
			cout << "Invalid format" << endl;
			exit(1);
		}
	}

	in_file.close();
}