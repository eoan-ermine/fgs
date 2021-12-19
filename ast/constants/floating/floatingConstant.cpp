#include <cstddef>
#include <string>

#include "llvm/IR/Constants.h"
#include "llvm/ADT/APFloat.h"

#include "floatingConstant.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

FloatingConstant::FloatingConstant(double value): value(value) { }
llvm::Value* FloatingConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
	return llvm::ConstantFP::get(
		codegenState.context,
		llvm::APFloat(value)
	);
}

FloatingConstant parseFloatingConstant(const std::string& number) {
	return FloatingConstant(std::stod(number));
}

}
