#pragma once

#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"

#include "state.hpp"

class ASTNode {
public:
	virtual llvm::Value* codegen(
		State& state,
		llvm::LLVMContext& context
	) = 0;
};