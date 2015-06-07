#include <iostream>
#include "PersistentVector.h"

void testGetAt(int k, const PersistentVector<int>& v)
{
	std::cout << "temp.operator[" << k << "] = " << v[k] << std::endl;
}

int main()
{
	/*PersistentVector<int> pv1;
	PersistentVector<int> pv2 = pv1.append(5);
	PersistentVector<int> pv3 = pv1.append(15);
	PersistentVector<int> pv4 = pv3.append(35);
	pv1.print(std::cout);
	pv2.print(std::cout);
	pv3.print(std::cout);
	pv4.print(std::cout);*/

	const int COUNT = 32*33 + 1 + 1; // from 0 to 35  (so + 1 element for 0, and +1 for empty vector).

	// NOTE the first vector is empty one. so valus from 0 to count - 2 (count - 1 but the first one is empty)
	PersistentVector<int> arr[COUNT];

	for (int i = 0; i < COUNT - 1; ++i)
	{
		arr[i + 1] = arr[i].append(i);
	}

	arr[COUNT - 1].print(std::cout);
	PersistentVector<int>  temp = arr[COUNT - 1];

	testGetAt(0, temp);
	testGetAt(31, temp);
	testGetAt(32, temp);
	testGetAt(1024, temp);
	testGetAt(1021, temp);
	testGetAt(1048, temp);
	testGetAt(1056, temp);

	return 0;
}
