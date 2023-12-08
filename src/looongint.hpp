#pragma once

#include <string>
#include <list>

class LooongInt {
public:
	LooongInt() noexcept;
	LooongInt(const char* number) noexcept;
	LooongInt(const std::string& number) noexcept;

	LooongInt operator+(const LooongInt& other) noexcept;
	LooongInt operator*(const LooongInt& other) noexcept;

	std::string get() noexcept;

private:
	using Data = std::list<uint8_t>;

	static constexpr uint8_t base = 10;
	
	Data data;
	bool isNegative = false;

	static Data add(const Data& longer, const Data& shorter) noexcept;
	static Data karatsubaMul(const Data& longer, const Data& shorter) noexcept;

};


