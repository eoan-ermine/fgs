#pragma once

#include <string>
#include <string_view>

#include "llvm/ADT/APFloat.h"

namespace fgs::common {

class Floating {
	llvm::APFloat value;
public:
	Floating(const std::string& floating);
	operator const llvm::APFloat&() const;
};

}

namespace fgs::common::detail {

enum class FloatingType {
	Float,
	Double,
	LongDouble
};

FloatingType determineFloatingType(std::string_view floating);

enum class FloatingFormatType {
	Hexadecimal = 16,
	Decimal = 10
};

FloatingFormatType determineFloatingFormatType(std::string_view floating);

class FloatingConstantType {
	FloatingType floatingType;
	FloatingFormatType formatType;
public:
	FloatingConstantType(std::string_view floating);
	FloatingType getFloatingType() const;
	FloatingFormatType getFormatType() const;
};

class FloatingOffset {
	std::size_t left;
	std::size_t right;
public:
	FloatingOffset(std::string_view floating, FloatingConstantType type);
	std::size_t getLeftBorder() const;
	std::size_t getRightBorder() const;
};

std::string extractFloating(const std::string& floating, FloatingConstantType type);

}