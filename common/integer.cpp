#include "llvm/ADT/StringRef.h"

#include "integer.hpp"

using namespace fgs::common;
using namespace fgs::common::detail;

namespace fgs::common {

Integer::Integer(const std::string& integer) {
	using namespace detail;

	auto type = IntegerConstantType(integer);
	std::string extractedInteger = extractInteger(integer, type);
	value = llvm::APInt(64, llvm::StringRef(extractedInteger), static_cast<uint8_t>(type.getFormatType()));

	unsigned bitWidth = value.ceilLogBase2();

	if(bitWidth <= 16) bitWidth = 16;
	else if(bitWidth <= 32) bitWidth = 32;
	value = value.trunc(bitWidth);
}

Integer::operator const llvm::APInt&() const {
	return value;
}

}

namespace fgs::common::detail {

IntegerSignedness determineIntegerSignedness(std::string_view integer) {
	bool unsignedSuffixFound = (integer.find('u') != std::string::npos) ||
									(integer.find('U') != std::string::npos);
	return unsignedSuffixFound ? IntegerSignedness::Unsigned : IntegerSignedness::Default;
}

IntegerWidth determineIntegerWidth(std::string_view integer) {
	bool longLongSuffixFound = (integer.find("ll") != std::string::npos) ||
									(integer.find("LL") != std::string::npos);
	return longLongSuffixFound ? IntegerWidth::LongLong : IntegerWidth::Default;
}

IntegerType::IntegerType(std::string_view integer): signedness{
	determineIntegerSignedness(integer)
}, width{
	determineIntegerWidth(integer)
} { }

IntegerSignedness IntegerType::getSignedness() const {
	return signedness;
}
IntegerWidth IntegerType::getWidth() const {
	return width;
}

IntegerFormatType determineIntegerFormatType(std::string_view integer) {
	if(integer.starts_with('0')) {
		return IntegerFormatType::Octal;
	} else if(integer.starts_with("0x") || integer.starts_with("0X")) {
		return IntegerFormatType::Hexadecimal;
	} else if(integer.starts_with("0b") || integer.starts_with("0B")) {
		return IntegerFormatType::Binary;
	}

	return IntegerFormatType::Decimal;
}

IntegerConstantType::IntegerConstantType(std::string_view integer): integerType{
	integer
}, formatType{
	determineIntegerFormatType(integer)
} { }

IntegerType IntegerConstantType::getIntegerType() const {
	return integerType;
}

IntegerFormatType IntegerConstantType::getFormatType() const {
	return formatType;
}

IntegerOffset::IntegerOffset(std::string_view integer, IntegerConstantType type): left{}, right{integer.size()} {
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

std::size_t IntegerOffset::getLeftBorder() const {
	return left;
}

std::size_t IntegerOffset::getRightBorder() const {
	return right;
}

std::string extractInteger(const std::string& integer, IntegerConstantType type) {
	IntegerOffset offset{integer, type};
	return integer.substr(offset.getLeftBorder(), offset.getRightBorder());
}

}