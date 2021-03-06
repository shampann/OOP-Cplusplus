#include "Utility.h"

// Returns the length of the char string.

size_t strLength(const char* str)
{
	size_t length = 0;

	while (*str++)
	{
		++length;
	}

	return length;
}


void strCopy(char * dest, const char* src)
{
	if (dest && src)
	{
		do
		{
			*dest++ = *src;
		} while (*src++); // including '\0'

	}
}

// gets a string till match of new line or EOF, saves the data in the given one ('str').

void getLineFromIStream(std::istream & in, MyString& str)
{
	getDataFromIStream(in, str, checkNewLine);
}

// Gets the symbols from input stream till match of new line or EOF or space, saves the data in the given one ('str')

void getWordFromIStream(std::istream & in, MyString& str)
{
	getDataFromIStream(in, str, checkNewWord);
}

// Gets the symbols from input stream till match of given function.

void getDataFromIStream(std::istream & in, MyString& str, bool(*pFunc)(char ch))
{
	str = ""; // empty string.

	if (!in)
		throw "The input is broken!";

	char ch;

	do
	{
		in.get(ch);
		if (!in)
			throw "The input is broken!";

		if (pFunc(ch))
			str += ch;
		else
			break;
	} while (in);
}

bool checkNewLine(char ch)
{
	return ch != EOF && ch != '\n';
}

bool checkNewWord(char ch)
{
	return ch != EOF && ch != '\n' && ch != ' ';
}


MyString* parseThePath(const MyString& path, char delim, size_t size)
{
	MyString * arr = new MyString[size];

	const char* pStr = path.getString();

	MyString dir;

	for (size_t i = 0; i < size; ++i)
	{
		dir = "";

		while (*pStr && *pStr != delim)
		{
			dir += *pStr;
			++pStr;
		}

		++pStr;
		
		arr[i] = dir;
	}

	return arr;
}


size_t getCountDirectories(const MyString& path, char delim)
{
	size_t count = 1;
	const char* pStr = path.getString();
	
	while (*pStr)
	{
		if (*pStr == delim)
			++count;
		
		++pStr;
	}

	return count;
}

// Check if the user whant`s some action ti happen(the action is given by the 'msg'. If he enter "y" or "Y" returns true, in any other case returns false.

bool checkForAction(std::istream & in, std::ostream & out, const MyString& msg)
{
	out << msg << "? (y?) ";

	MyString str;

	getLineFromIStream(in, str);

	return str == "y" || str == "Y";
}