#pragma once

#include <string>
#include <string_view>

#include "llvm/ADT/APInt.h"

namespace fgs::common {

class Integer {
	llvm::APInt value;
public:
	Integer(const std::string& integer);
	operator const llvm::APInt&() const;
};

}

namespace fgs::common::detail {

enum class IntegerSignedness {
	Default,
	Unsigned
};

IntegerSignedness determineIntegerSignedness(std::string_view integer);

enum class IntegerWidth {
	Default,
	LongLong
};

IntegerWidth determineIntegerWidth(std::string_view integer);

class IntegerType {
	IntegerSignedness signedness;
	IntegerWidth width;
public:
	IntegerType(std::string_view integer);
	IntegerSignedness getSignedness() const;
	IntegerWidth getWidth() const;
};

enum class IntegerFormatType {
	Binary = 2,
	Octal = 8,
	Decimal = 10,
	Hexadecimal = 16
};

IntegerFormatType determineIntegerFormatType(std::string_view integer);

class IntegerConstantType {
	IntegerType integerType;
	IntegerFormatType formatType;
public:
	IntegerConstantType(std::string_view integer);
	IntegerType getIntegerType() const;
	IntegerFormatType getFormatType() const;
};

class IntegerOffset {
	std::size_t left;
	std::size_t right;
public:
	IntegerOffset(std::string_view integer, IntegerConstantType type);
	std::size_t getLeftBorder() const;
	std::size_t getRightBorder() const;
};

std::string extractInteger(const std::string& integer, IntegerConstantType type);

}