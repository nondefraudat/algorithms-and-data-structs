// Time 
//	worst	O(n log n)
//	average	O(n log n)
//	best	O(n log n)
// Memm	&& O(n)
template <typename T>
T* mergeSort(T* const data, const size_t size) noexcept {
	if (!size) {
		return nullptr;
	}

	if (size == 1) {
		return new T(*data);
	}

	size_t leftSize(size/2);
	size_t rightSize(size - leftSize);
	
	T* const leftData = mergeSort<T>(data, leftSize);
	T* const rightData = mergeSort<T>(&data[leftSize], rightSize);

	T* const sorted = new T[size];
	
	size_t leftIndex = 0, rightIndex = 0;

	for (int i = 0; i < size; i++) {
		if (rightIndex == rightSize ||
				leftIndex < leftSize &&
				leftData[leftIndex] < rightData[rightIndex]) {
			sorted[i] = leftData[leftIndex++];
		}
		else {
			sorted[i] = rightData[rightIndex++];
		}
	}

	delete[] leftData;
	delete[] rightData;

	return sorted;
}

