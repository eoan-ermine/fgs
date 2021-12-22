#include <type_traits>
#include <cstddef>
#include <string>

#include "llvm/IR/Constants.h"
#include "llvm/ADT/APFloat.h"

#include "floatingConstant.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

FloatingConstant::FloatingConstant(float value): value(value) { }
FloatingConstant::FloatingConstant(double value): value(value) { }
FloatingConstant::FloatingConstant(long double value): value(static_cast<double>(value)) { }

llvm::Value* FloatingConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
	if(const float* number = std::get_if<float>(&value)) {
        return llvm::ConstantFP::get(codegenState.context, llvm::APFloat(*number));
	}
	if(const double* number = std::get_if<double>(&value)) {
        return llvm::ConstantFP::get(codegenState.context, llvm::APFloat(*number));
	}
}

FloatingConstant FloatingConstant::parse(const std::string& number) {
	if(number.ends_with("l") || number.ends_with("L")) {
		return FloatingConstant(std::stold(number));
	} else if(number.ends_with("f") || number.ends_with("F")) {
		return FloatingConstant(std::stof(number));
	}
	return FloatingConstant(std::stod(number));
}

}
