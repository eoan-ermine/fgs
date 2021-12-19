#pragma once

#include <cstddef>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constants.h"

#include "ast/node.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

struct IntegerConstant: public ASTNode {
	int64_t value;
	llvm::Value* codegen() override {
		return llvm::ConstantInt::getSigned(
			llvm::Type::getInt64Ty(CodegenState{}.context),
			value
		);
	}
};

}
