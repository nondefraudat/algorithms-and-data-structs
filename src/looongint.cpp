#include "looongint.hpp"

using namespace std;

LooongInt::LooongInt() noexcept {
	data.push_back(0);
}

LooongInt::LooongInt(const char* const number) noexcept {
	const char* it = number;
	if (*it == '-') {
		isNegative = true;
		it++;
	}
	for (it; *it; it++) {
		data.push_back(*it - '0');
	}
}

LooongInt::LooongInt(const std::string& number) noexcept 
		: LooongInt(number.c_str()) { }

LooongInt LooongInt::operator+(const LooongInt& other) const noexcept {
	LooongInt result;
	const Ratio ratio = compare(data, other.data);
	if (isNegative != other.isNegative) {
		if (ratio != Ratio::equal) {
			result.data = ratio == Ratio::more
					? subtract(data, other.data)
					: subtract(other.data, data);
			result.isNegative = isNegative && ratio == Ratio::more;
		}
		return result;
	}
	result.data = ratio == Ratio::more
			? add(data, other.data)
			: add(other.data, data);
	result.isNegative = isNegative;
	return result;
}

LooongInt LooongInt::operator-(const LooongInt& other) const noexcept {
	LooongInt result;
	const Ratio ratio = compare(data, other.data);
	if (isNegative == other.isNegative) {
		if (ratio != Ratio::equal) {
			result.data = ratio == Ratio::more
				? subtract(data, other.data)
				: subtract(other.data, data);
			result.isNegative = isNegative == (ratio == Ratio::more);
		}
		return result;
	}
	result.data = ratio == Ratio::more
		? add(data, other.data)
		: add(other.data, data);
	result.isNegative = isNegative;
	return result;
}

LooongInt LooongInt::operator*(const LooongInt& other) const noexcept {
	LooongInt result(karatsuba(data, other.data));
	while (result.data.front() == 0) {
		result.data.pop_front();
	}
	result.isNegative = isNegative^other.isNegative;
	return result;
}

std::string LooongInt::get() const noexcept {
	string definition;
	if (isNegative) {
		definition.push_back('-');
	}
	for (const uint8_t digit : data) {
		definition.push_back('0' + digit);
	}
	return definition;
}

LooongInt::LooongInt(const Data& data) noexcept : data(data) { }

LooongInt::Ratio LooongInt::compare(const Data& left,
		const Data& right) noexcept {
	if (left.size() > right.size()) {
		return Ratio::more;
	}
	if (left.size() < right.size()) {
		return Ratio::less;
	}
	for (auto lIt = left.cbegin(), rIt = right.cbegin();
			lIt != left.cend(); lIt++, rIt++) {
		if (*lIt > *rIt) {
			return Ratio::more;
		}
		if (*lIt < *rIt) {
			return Ratio::less;
		}
	}
	return Ratio::equal;
}

LooongInt::Data LooongInt::addSafe(const Data& left, const Data& right,
		const uint8_t base) noexcept {
	return left.size() > right.size() ? add(left, right) : add(right, left);
}

LooongInt::Data LooongInt::add(const Data& larger,
		const Data& smaller, const uint8_t base) noexcept {
	Data result;
	auto lIt = larger.crbegin();
	uint8_t excess(0);
	for (auto sIt = smaller.crbegin();
			sIt != smaller.crend(); sIt++, lIt++) {
		const uint8_t buffer((*lIt + excess) + *sIt);
		result.push_front(buffer%base);
		excess = buffer/base;
	}
	if (lIt != larger.crend() && excess) {
		result.push_front(*lIt + excess);
		excess = 0;
		lIt++;
	}
	while (lIt != larger.crend()) {
		result.push_front(*lIt++);
	}
	if (excess) {
		result.push_front(excess);
	}
	return result;
}

LooongInt::Data LooongInt::subtract(const Data& larger,
		const Data& smaller, const uint8_t base) noexcept {
	Data result;
	auto lIt = larger.crbegin();
	uint8_t loss(0);
	for (auto sIt = smaller.crbegin();
			sIt != smaller.crend() &&
			lIt != larger.crend(); lIt++, sIt++) {
		const uint8_t buffer((base + *lIt) - (*sIt + loss));
		result.push_front(buffer%base);
		loss = buffer < base;
	}
	for (lIt; lIt != larger.crend(); lIt++) {
		const uint8_t buffer((base + *lIt) - loss);
		result.push_front(buffer%base);
		loss = buffer < base;
	}
	return result;
}
LooongInt::Data LooongInt::karatsuba(const Data& left,
		const Data& right, const uint8_t base) noexcept {
	const size_t optimal(findOptimalSize(left.size(), right.size()));
	if (optimal == 1) {
		Data result;
		const uint8_t buffer(left.front()*right.front());
		result.push_front(buffer%base);
		result.push_front(buffer/base);
		return result;
	}
	Data a, b, c, d;
	tie(a, b) = splitOptimized(left, optimal);
	tie(c, d) = splitOptimized(right, optimal);

	// Step 1
	
	Data ac = karatsuba(a, c);
	
	// Step 2
	
	const Data& bd = karatsuba(b, d);
	
	// Step 3
	
	const Data& a_b = add(a, b);
	const Data& c_d = add(c, d);
	const Data& a_bXc_d = karatsuba(a_b, c_d);
	
	// Step 4
	
	const Data& ac_bd = addSafe(ac, bd);
	Data sub = subtract(a_bXc_d, ac_bd);
	
	// Step 5
	
	for (size_t i = 0; i < optimal; i++) {
		ac.push_back(0);
	}
	for (size_t i = 0; i < optimal/2; i++) {
		sub.push_back(0);
	}
	
	const Data& sum = addSafe(ac, bd);

	return addSafe(sum, sub);
}

size_t LooongInt::findOptimalSize(const size_t left,
		const size_t right) noexcept {
	size_t optimalSize = 1;
	const size_t maxSize = left > right ? left : right;
	while (optimalSize < maxSize) {
		optimalSize *= 2;
	}
	return optimalSize;
}

std::tuple<LooongInt::Data, LooongInt::Data> LooongInt::splitOptimized(
		const Data& source,
		const size_t optimal) noexcept {
	auto it = source.crbegin();
	const size_t size(optimal/2);
	const Data& right = extractFixedSize(it, source.crend(), size);
	const Data& left = extractFixedSize(it, source.crend(), size);
	return std::tuple<Data, Data>(left, right);
}

LooongInt::Data LooongInt::extractFixedSize(Data::const_reverse_iterator& it,
		const Data::const_reverse_iterator& terminator,
		const size_t size) noexcept {
	Data data;
	size_t counter = size;
	for (it; it != terminator && counter; it++, counter--) {
		data.push_front(*it);
	}
	for (counter; counter; counter--) {
		data.push_front(0);
	}
	return data;
}
