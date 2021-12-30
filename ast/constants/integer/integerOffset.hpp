#pragma once

#include "integerConstantType.hpp"

namespace fgs::ast {

class IntegerOffset {
	std::size_t left;
	std::size_t right;
public:
	IntegerOffset(const std::string& integer, IntegerConstantType type): left{}, right{integer.size()} {
		IntegerType integerType = type.getIntegerType();
		switch(integerType.getSignedness()) {
			case IntegerSignedness::Unsigned:
				right -= 1;
				break;
		}
		switch(integerType.getWidth()) {
			case IntegerWidth::LongLong:
				right -= 1;
				break;
		}

		switch(type.getFormatType()) {
			case IntegerFormatType::Binary:
			case IntegerFormatType::Hexadecimal:
				left += 2;
				break;
		}
	}

	std::size_t getLeftBorder() const {
		return left;
	}

	std::size_t getRightBorder() const {
		return right;
	}
};

std::string extractInteger(const std::string& integer, IntegerConstantType type) {
	IntegerOffset offset{integer, type};
	return integer.substr(offset.getLeftBorder(), offset.getRightBorder());
}

}