#include "floating.hpp"

namespace fgs::common {

Floating::Floating(const std::string& floating): value(0.0) {
	using namespace detail;

	auto type = FloatingConstantType(floating);
	auto extractedNumber = extractFloating(floating, type);
	value = [&]() {
		switch(type.getFloatingType()) {
			case FloatingType::Float:
				return llvm::APFloat(llvm::APFloat::IEEEsingle(), extractedNumber);
			case FloatingType::Double:
				return llvm::APFloat(llvm::APFloat::IEEEdouble(), extractedNumber);
			case FloatingType::LongDouble:
				return llvm::APFloat(llvm::APFloat::x87DoubleExtended(), extractedNumber);
		}
	}();
}

Floating::operator const llvm::APFloat&() const {
	return value;
}

}

namespace fgs::common::detail {

FloatingType determineFloatingType(std::string_view floating) {
	if(floating.ends_with('f') || floating.ends_with('F')) {
		return FloatingType::Float;
	} else if(floating.ends_with('l') || floating.ends_with('L')) {
		return FloatingType::LongDouble;
	}
	return FloatingType::Double;
}
FloatingFormatType determineFloatingFormatType(std::string_view floating) {
	if(floating.starts_with("0x") || floating.starts_with("0X")) {
		return FloatingFormatType::Hexadecimal;
	}

	return FloatingFormatType::Decimal;
}

FloatingConstantType::FloatingConstantType(std::string_view floating): floatingType{
	determineFloatingType(floating)
}, formatType{
	determineFloatingFormatType(floating)
} { }

FloatingType FloatingConstantType::getFloatingType() const {
	return floatingType;
}

FloatingFormatType FloatingConstantType::getFormatType() const {
	return formatType;
}

FloatingOffset::FloatingOffset(std::string_view floating, FloatingConstantType type): left{}, right{floating.size()} {
	switch(type.getFloatingType()) {
		case FloatingType::Float:
		case FloatingType::LongDouble:
			right -= 1;
			break;
	}
	switch(type.getFormatType()) {
		case FloatingFormatType::Hexadecimal:
			left += 2;
			break;
	}
}

std::size_t FloatingOffset::getLeftBorder() const {
	return left;
}

std::size_t FloatingOffset::getRightBorder() const {
	return right;
}

std::string extractFloating(const std::string& floating, FloatingConstantType type) {
	FloatingOffset offset{floating, type};
	return floating.substr(offset.getLeftBorder(), offset.getRightBorder());
}

}