#pragma once

#include "../astNode.hpp"
#include "llvm/IR/Constants.h"

#include <climits>

class characterConstant: ASTNode {
	int value;
public:
	characterConstant(int value_): value(value_) { }
	llvm::Value* codegen(llvm::LLVMContext& context) {
		return llvm::ConstantInt::get(
			context, llvm::APInt(sizeof(int) * CHAR_BIT, value)
		);
	}
};