#include "../misc/xorswap.inc"

// Time 
//	worst	O(n^2)
//	average	O(n^2)
//	best	O(n^2)
// Memm	O(n) && O(1)
template<typename T>
void selectionSort(T* const inOut, const size_t size) noexcept {
	for (size_t i = 0; i < size; i++) {
		size_t localMinIndex = i;
		for (size_t j = i + 1; j < size; j++) {
			if (inOut[j] < inOut[localMinIndex]) {
				localMinIndex = j;
			}
		}
		if (localMinIndex != i) {
			xorSwap<T>(inOut[i], inOut[localMinIndex]);
		}
	}
}
