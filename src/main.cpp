#include "sorts/mergesort.inc"
#include "misc/countinversions.inc"
#include <iostream>

using namespace std;

int main() {
	int ok[] = { 2, 3, 5, -1, 3, 4, 5, 8, 7, 1 };
	const size_t size(_countof(ok));

	cout << "source array: { ";
	for (int i : ok) {
		cout << i << ", ";
	}
	cout << "}\ninversions count: " <<
			countInversions<int>(ok, size) << endl;
	
	int* kk = mergeSort<int>(ok, size);
	cout << "sorted array: { ";
	for (int i = 0; i < size; i++) {
		cout << kk[i] << ", ";
	}
	cout << "}\ninversions count: " <<
		countInversions<int>(kk, size) << endl;

	return 0;
}