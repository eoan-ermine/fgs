#pragma once

#include <cmath>

enum class Base {
	Decimal,
	Octal,
	Hexadecimal
};

unsigned int getIntegerByteWidth(__int128 integer) {
		unsigned int bitWidth = std::ceil(std::log2(integer));
		unsigned int byteWidth = std::ceil(bitWidth / 8.0);

		if(byteWidth >= 0 && byteWidth <= sizeof(int)) {
			return sizeof(int);
		} else if(byteWidth > sizeof(int) && byteWidth <= sizeof(unsigned int)) {
			return sizeof(unsigned int);
		} else if(byteWidth > sizeof(unsigned int) && byteWidth <= sizeof(long unsigned int)) {
			return sizeof(long unsigned int);
		}
}