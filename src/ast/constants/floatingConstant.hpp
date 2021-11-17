#pragma once

#include "../astNode.hpp"
#include "llvm/IR/Constants.h"

class floatingConstant: ASTNode {
	double value;
public:
	floatingConstant(double value_): value(value_) { }
	llvm::Value* codegen(State&, llvm::LLVMContext& context) {
		return llvm::ConstantFP::get(
			context, llvm::APFloat(value)
		);
	}
};