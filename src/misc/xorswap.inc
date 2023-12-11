template<typename T>
void xorSwap(T& left, T& right) noexcept {
	left ^= right;
	right ^= left;
	left ^= right;
}