#include <iostream>
#include "String.h"

#include <crtdbg.h>

int main()
{
	//_CrtMemState s1, s2, s3;
	//_CrtMemCheckpoint(&s1);
	//{

	//	String tony = "Tony";
	//	std::cout << tony << std::endl;

	//}

	//_CrtMemCheckpoint(&s2);

	//if (_CrtMemDifference(&s3, &s1, &s2))
	//{
	//	std::cout << "Memory leak detected!" << std::endl;
	//	_CrtMemDumpStatistics(&s3);
	//}


		try
		{
			new char;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}

		_CrtDumpMemoryLeaks();

	return 0;
}