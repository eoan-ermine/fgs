#include <type_traits>
#include <cstddef>
#include <string>

#include "llvm/IR/Constants.h"
#include "llvm/ADT/APFloat.h"

#include "floatingConstant.hpp"
#include "floatingOffset.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

FloatingConstant::FloatingConstant(double value, FloatingConstantType type): value(value), type(type) { }

llvm::Value* FloatingConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
	auto value = [&]() -> llvm::APFloat {
		switch(type.getFloatingType()) {
			case FloatingType::Float:
				return llvm::APFloat(static_cast<float>(this->value));
			case FloatingType::Double:
			case FloatingType::LongDouble:
				return llvm::APFloat{this->value};
		}
	}();
    return llvm::ConstantFP::get(codegenState.context, value);
}

FloatingConstant FloatingConstant::parse(const std::string& number) {
	auto type = FloatingConstantType(number);
	auto extractedNumber = extractFloating(number, type);
	return FloatingConstant(std::stod(extractedNumber), FloatingConstantType(number));
}

}
