template<typename T>
void insertionSort(T* const inOut, const size_t size) noexcept {
	for (size_t i = 1; i < size; i++) {
		T currVal = inOut[i];
		size_t j = i;
		for (j; j > 0 && inOut[j - 1] > currVal; j--) {
			inOut[j] = inOut[j - 1];
		}
		inOut[j] = currVal;
	}
}
