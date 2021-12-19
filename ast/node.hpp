#pragma once

#include "llvm/IR/Value.h"

namespace fgs::ast {

struct ASTNode {
	ASTNode* left;
	ASTNode* right;

	virtual ~ASTNode() { };
	virtual llvm::Value* codegen() = 0;
};

}
