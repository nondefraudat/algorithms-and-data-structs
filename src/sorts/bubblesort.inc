#include "../misc/xorswap.inc"

// Time O(n) O(n^2) O(n^2)
// Memm O(1)
template<typename T>
void bubbleSort(T* const inOut, const size_t size) noexcept {
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size - i; j++) {
			if (inOut[j + 1] < inOut[j]) {
				xorSwap<T>(inOut[j + 1], inOut[j]);
			}
		}
	}
}