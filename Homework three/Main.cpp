/*

	#71488 FMI 
	Homework three

	Github repository: https://github.com/Anton94/OOP-Cplusplus
	Github project:	   https://github.com/Anton94/OOP-Cplusplus/tree/master/Homework%20three

*/

#include <iostream>
#include "MyTestStruct.h"
#include "Test.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "QuickSort.h"
#include "SelectionSort.h"
#include "ShakerSort.h"


int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		InsertionSort<MyTestStruct> insertionSort;
		MergeSort<MyTestStruct> mergeSort;
		HeapSort<MyTestStruct> heapSort;
		QuickSort<MyTestStruct> quickSort;
		SelectionSort<MyTestStruct> selectionSort;
		ShakerSort<MyTestStruct> shakerSort;

		Sorter<MyTestStruct> ** sorters = new Sorter<MyTestStruct>*[6];

		sorters[0] = &insertionSort;
		sorters[1] = &mergeSort;
		sorters[2] = &heapSort;
		sorters[3] = &quickSort;
		sorters[4] = &selectionSort;
		sorters[5] = &shakerSort;
		Test<MyTestStruct> test(sorters, 6);
		test.getSummary(std::cout);

		delete[] sorters;
	}


	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}

	return 0;
}