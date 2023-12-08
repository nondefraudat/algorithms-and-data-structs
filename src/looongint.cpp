#include "looongint.hpp"

using namespace std;

LooongInt::LooongInt() noexcept {
	data.push_back(0);
}

LooongInt::LooongInt(const char* number) noexcept {
	const char* it = number;
	if (*it == '-') {
		isNegative = true;
		it++;
	}
	while (*it) {
		data.push_back(static_cast<uint8_t>(*it++ - '0'));
	}
}

LooongInt::LooongInt(const std::string& number) noexcept
	: LooongInt(number.c_str()) { }

LooongInt LooongInt::operator+(const LooongInt& other) noexcept {
	LooongInt result;
	if (this->data.size() >= other.data.size()) {
		result.data = add(this->data, other.data);
	}
	else {
		result.data = add(other.data, this->data);
	}
	return result;
}

LooongInt LooongInt::operator*(const LooongInt& other) noexcept {

	return LooongInt();
}

std::string LooongInt::get() noexcept {
	string definition("");
	for (const uint8_t digit : data) {
		definition.push_back('0' + digit);
	}
	return definition;
}

LooongInt::Data LooongInt::add(const Data& longer,
		const Data& shorter) noexcept {
	Data result;
	uint8_t excess = 0;
	Data::const_reverse_iterator lIt = longer.crbegin();
	for (Data::const_reverse_iterator sIt = shorter.crbegin();
			sIt != shorter.crend(); sIt++, lIt++) {
		const uint8_t buffer(*sIt + *lIt + excess);
		result.push_front(buffer%base);
		excess = buffer/base;
	}
	if (lIt != longer.crend() && excess) {
		result.push_front(*lIt++ + excess);
	}
	for (lIt; lIt != longer.crend(); lIt++) {
		result.push_front(*lIt);
	}
	if (excess) {
		result.push_front(excess);
	}
	return result;
}
