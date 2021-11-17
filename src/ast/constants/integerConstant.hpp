#pragma once

#include "../astNode.hpp"
#include "llvm/IR/Constants.h"

#include "types/integer.hpp"

class integerConstant: ASTNode {
	__int128 value;
public:
	integerConstant(__int128 value_): value(value_) { }
	llvm::Value* codegen(State&, llvm::LLVMContext& context) {
		return llvm::ConstantInt::get(
			context, llvm::APInt(getIntegerByteWidth(value) * CHAR_BIT, value)
		);
	}
};