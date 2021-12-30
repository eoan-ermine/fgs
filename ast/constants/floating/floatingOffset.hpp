#pragma once

#include <string_view>
#include "floatingConstantType.hpp"

namespace fgs::ast {

class FloatingOffset {
	std::size_t left;
	std::size_t right;
public:
	FloatingOffset(std::string_view floating, FloatingConstantType type): left{}, right{floating.size()} {
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

	std::size_t getLeftBorder() const {
		return left;
	}

	std::size_t getRightBorder() const {
		return right;
	}
};

std::string extractFloating(const std::string& floating, FloatingConstantType type) {
	FloatingOffset offset{floating, type};
	return floating.substr(offset.getLeftBorder(), offset.getRightBorder());
}

}