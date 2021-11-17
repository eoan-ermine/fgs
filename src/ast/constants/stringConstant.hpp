#pragma once

#include "../astNode.hpp"
#include "llvm/IR/Constants.h"

class stringConstant: ASTNode {
	std::string value;
public:
	floatingConstant(const std::string& value_): value(value_) { }
	llvm::Value* codegen(State&, llvm::LLVMContext& context) {
		return llvm::ConstantDataArray::getString(
			context, value, true
		);
	}
};