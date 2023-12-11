#include "clone.inc"

template<typename T>
size_t sortAndGetInversionsCount(T*& dataInOut, const size_t size) noexcept {
	if (size <= 1) {
		return 0;
	}
	
	const size_t leftSize(size/2);
	const size_t rightSize(size - leftSize);

	T* leftData = clone<T>(dataInOut, leftSize);
	T* rightData = clone<T>(&dataInOut[leftSize], rightSize);

	const size_t leftInversionCount = sortAndGetInversionsCount<T>(leftData, leftSize);
	const size_t rightInversionCount = sortAndGetInversionsCount<T>(rightData, rightSize);

	size_t leftIndex = 0;
	size_t rightIndex = 0;

	size_t inversinsCount = leftInversionCount + rightInversionCount;

	for (int i = 0; i < size; i++) {
		if (rightIndex == rightSize ||
				leftIndex < leftSize &&
				leftData[leftIndex] < rightData[rightIndex]) {
			dataInOut[i] = leftData[leftIndex++];
		}
		else {
			if (leftIndex < leftSize &&
					rightData[rightIndex] < leftData[leftIndex]) {
				inversinsCount++;
			}
			dataInOut[i] = rightData[rightIndex++];
		}
	}

	delete leftData;
	delete rightData;

	return inversinsCount;
}

template<typename T>
size_t countInversions(T* const from, const size_t size) noexcept {
	T* dataClone = clone<T>(from, size);
	return sortAndGetInversionsCount<T>(dataClone, size);
}
