#include <vector>
#include <algorithm>

void heapSort(std::vector<int>& values) {
	std::make_heap(values.begin(), values.end());
	for (auto i = values.end(); i != values.begin(); --i) {
		std::pop_heap(values.begin(), i);
	}
}