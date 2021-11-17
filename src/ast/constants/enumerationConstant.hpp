#pragma once

#include "../astNode.hpp"
#include "llvm/IR/Constants.h"

#include <stdexcept>

class enumerationConstant: ASTNode {
	std::string identifier;
public:
	enumerationConstant(const std::string& ident): identifier(ident) { }
	llvm::Value* codegen(State& state, llvm::LLVMContext& context) {
		llvm::Value *V = state.getEnumerations()[identifier];
		if(!V) {
			throw std::runtime_error{"Unknown enumeration constant"};
		}
		return V;
	}
};