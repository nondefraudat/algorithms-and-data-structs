#include "../misc/xorswap.inc"

// Time 
//	worst	O(n^2)
//	average	O(n^2/2*incCount)
//	best	O(n log n)
// Memm	O(1)
template<typename T>
void combSort(T* const inOut, const size_t size) {
	const double factor(1.247);
	double step = size - 1;
	while (step >= 1) {
		for (size_t left = 0, right = step;
				right < size; left++, right++) {
			if (inOut[right] < inOut[left]) {
				xorSwap<T>(inOut[right], inOut[left]);
			}
		}
		step /= factor;
	}
}
