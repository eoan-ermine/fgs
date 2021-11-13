#pragma once

#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"

class ASTNode {
public:
	virtual llvm::Value* codegen(
		llvm::LLVMContext& context
	) = 0;
};