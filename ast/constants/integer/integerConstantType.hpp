#pragma once

#include <algorithm>
#include <string>

namespace fgs::ast {

enum class IntegerSignedness {
	Default,
	Unsigned
};

IntegerSignedness determineIntegerSignedness(const std::string& integer) {
	bool unsignedSuffixFound = (integer.find('u') != std::string::npos) ||
									(integer.find('U') != std::string::npos);
	return unsignedSuffixFound ? IntegerSignedness::Unsigned : IntegerSignedness::Default;
}

enum class IntegerWidth {
	Default,
	LongLong
};

IntegerWidth determineIntegerWidth(const std::string &integer) {
	bool longLongSuffixFound = (integer.find("ll") != std::string::npos) ||
									(integer.find("LL") != std::string::npos);
	return longLongSuffixFound ? IntegerWidth::LongLong : IntegerWidth::Default;
}

class IntegerType {
	IntegerSignedness signedness;
	IntegerWidth width;
public:
	IntegerType(const std::string& integer): signedness{
		determineIntegerSignedness(integer)
	}, width{
		determineIntegerWidth(integer)
	} { }

	IntegerSignedness getSignedness() const {
		return signedness;
	}
	IntegerWidth getWidth() const {
		return width;
	}
};

enum class IntegerFormatType {
	Binary = 2,
	Octal = 8,
	Decimal = 10,
	Hexadecimal = 16
};

IntegerFormatType determineIntegerFormatType(const std::string& integer) {
	if(integer.starts_with('0')) {
		return IntegerFormatType::Octal;
	} else if(integer.starts_with("0x") || integer.starts_with("0X")) {
		return IntegerFormatType::Hexadecimal;
	} else if(integer.starts_with("0b") || integer.starts_with("0B")) {
		return IntegerFormatType::Binary;
	}

	return IntegerFormatType::Decimal;
}

class IntegerConstantType {
	IntegerType integerType;
	IntegerFormatType formatType;
public:
	IntegerConstantType(const std::string& integer): integerType{
		integer
	}, formatType{
		determineIntegerFormatType(integer)
	} { }

	IntegerType getIntegerType() const {
		return integerType;
	}

	IntegerFormatType getFormatType() const {
		return formatType;
	}
};

}