#pragma once

#include <string_view>

namespace fgs::ast {

enum class FloatingType {
	Float,
	Double,
	LongDouble
};

enum class FloatingFormatType {
	Hexadecimal,
	Decimal
};

class FloatingConstantType {
	FloatingType floatingType;
	FloatingFormatType formatType;

	static FloatingType determineFloatingType(std::string_view floating) {
		if(floating.ends_with('f') || floating.ends_with('F')) {
			return FloatingType::Float;
		} else if(floating.ends_with('l') || floating.ends_with('L')) {
			return FloatingType::LongDouble;
		}
		return FloatingType::Double;
	}
	static FloatingFormatType determineFloatingFormatType(std::string_view floating) {
		if(floating.starts_with("0x") || floating.starts_with("0X")) {
			return FloatingFormatType::Hexadecimal;
		}

		return FloatingFormatType::Decimal;
	}
public:
	FloatingConstantType(std::string_view floating): floatingType{
		FloatingConstantType::determineFloatingType(floating)
	}, formatType{
		FloatingConstantType::determineFloatingFormatType(floating)
	} { }

	FloatingType getFloatingType() const {
		return floatingType;
	}

	FloatingFormatType getFormatType() const {
		return formatType;
	}
};

}