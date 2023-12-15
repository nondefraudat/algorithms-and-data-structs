#include <vector>
#include <algorithm>

// Time 
//	worst	O(n log n)
//	average	O(n log n)
//	best	O(n log n)
//		|| O(n) if values = { c, c, ..., c }
// Memm	O(n)
void heapSort(std::vector<int>& values) {
	std::make_heap(values.begin(), values.end());
	for (auto i = values.end(); i != values.begin(); --i) {
		std::pop_heap(values.begin(), i);
	}
}