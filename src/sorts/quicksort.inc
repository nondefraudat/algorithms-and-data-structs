#include "../misc/xorswap.inc"

// Time 
//	worst	O(n^2)
//	average	O(n log n)
//	best	O(n)
// Memm	O(n)
template<typename T>
size_t partition(T* const inOut,
		const size_t left, const size_t right) noexcept {
	T x = values[r];
	size_t less = l;

	for (size_t i = l; i < r; ++i) {
		if (values[i] <= x) {
			swap(values[i], values[less]);
			++less;
		}
	}
	swap(values[less], values[r]);
	return less;
}

template<typename T>
void quickSortImpl(T* const inOut,
		const size_t left, const size_t right) noexcept {
	if (left < right) {
		size_t lessIndex = partition(inOut, left, right);
		quickSortImpl<T>(inOut, left, lessIndex - 1);
		quickSortImpl<T>(inOut, lessIndex + 1, right);
	}
}

template<typename T>
void quickSort(T* const inOut, const size_t size) noexcept {
	if (!size) {
		quickSortImpl<T>(inOut, 0, size - 1);
	}
}
