#include <string>

#include "llvm/IR/Constants.h"

#include "integerConstant.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

IntegerConstant::IntegerConstant(const std::string& integer): value(integer) { }

llvm::Value* IntegerConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
	return llvm::ConstantInt::get(
		codegenState.context, value
	);
}

}
