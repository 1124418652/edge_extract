#include "stdafx.h"
#include "filename.h"

string getFileExtension(string file)
{
	int i;
	string extension;
	for (i = 0; file[i]; i++)
	{
		if (file[i] == '.')
			break;
	}
	for (; file[i]; i++) 
	{
		extension += file[i];
	}
	return extension;
}

string getFileExtension(CString file)
{
	int i;
	string extension;
	USES_CONVERSION;
	string filename = W2A(file);

	for (i = 0; file[i]; i++)
	{
		if (file[i] == '.')
			break;
	}
	for (; file[i]; i++)
	{
		extension += file[i];
	}
	return extension;
}