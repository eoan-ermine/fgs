#include <string>

#include "llvm/IR/Constants.h"

#include "floatingConstant.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

FloatingConstant::FloatingConstant(const std::string& floating): value(floating) { }

llvm::Value* FloatingConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
    return llvm::ConstantFP::get(codegenState.context, value);
}

}
