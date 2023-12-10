#include "sorts/mergesort.inc"
#include <iostream>

using namespace std;

int main() {
	int ok[] = { 2, 3, 5, -1, 3, 4, 5, 8, 7, 1 };
	for (int i : ok) {
		cout << i << " ";
	}
	cout << endl;
	int* kk = mergeSort<int>(ok, _countof(ok));
	for (int i = 0; i < _countof(ok); i++) {
		cout << kk[i] << " ";
	}
	cout << endl;
	return 0;
}