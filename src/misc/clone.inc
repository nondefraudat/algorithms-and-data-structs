template<typename T>
T* clone(T* const from, const size_t size) noexcept {
	if (!size) {
		return nullptr;
	}
	T* to = new T[size];
	for (size_t i = 0; i < size; i++) {
		to[i] = from[i];
	}
	return to;
}
