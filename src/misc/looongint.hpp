#pragma once

#include <string>
#include <list>
#include <tuple>

class LooongIntData;
struct LooongIntNode;

class LooongInt {
public:
	LooongInt() noexcept;
	LooongInt(const int64_t number) noexcept;
	LooongInt(const char* const number) noexcept;
	LooongInt(const std::string& number) noexcept;

	LooongInt operator+(const LooongInt& other) const noexcept;
	LooongInt operator-(const LooongInt& other) const noexcept;
	LooongInt operator*(const LooongInt& other) const noexcept;

	std::string get() const noexcept;

private:
	using Data = std::list<uint8_t>;
	enum class Ratio {
		more, less, equal
	};

	Data data;
	bool isNegative = false;
	uint8_t base = 10;

	LooongInt(const Data& data) noexcept;

	static Ratio compare(const Data& left, const Data& right) noexcept;
	static Data addSafe(const Data& left, const Data& right,
			const uint8_t base = 10) noexcept;
	static Data add(const Data& larger, const Data& smaller,
			const uint8_t base = 10) noexcept;
	static Data subtract(const Data& larger, const Data& smaller,
			const uint8_t base = 10) noexcept;
	static Data karatsuba(const Data& left, const Data& right,
			const uint8_t base = 10) noexcept;
	static size_t findOptimalSize(const size_t left,
			const size_t right) noexcept;
	static std::tuple<Data, Data> splitOptimized(const Data& source,
			const size_t optimal) noexcept;
	static Data extractFixedSize(Data::const_reverse_iterator& it,
			const Data::const_reverse_iterator& terminator,
			const size_t size) noexcept;
};
