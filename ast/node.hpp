#pragma once

#include "llvm/IR/Value.h"

namespace fgs::ast {

struct ASTNode {
	ASTNode* left;
	ASTNode* right;

	virtual ~ASTNode() = 0;
	virtual llvm::Value* codegen() = 0;
};

}
