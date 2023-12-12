#include "../misc/xorswap.inc"

template<typename T>
void cocktailSort(T* const inOut, const size_t size) noexcept {
	size_t leftIndex = 0;
	size_t rightIndex = size - 1;
	while (leftIndex < rightIndex) {
		for (size_t i = leftIndex; i < rightIndex; i++) {
			if (inOut[i + 1] < inOut[i]) {
				xorSwap<T>(inOut[i + 1], inOut[i]);
			}
		}
		rightIndex--;
		for (size_t i = rightIndex; i > leftIndex; i--) {
			if (inOut[i] < inOut[i - 1]) {
				xorSwap<T>(inOut[i], inOut[i - 1]);
			}
		}
		leftIndex++;
	}
}
