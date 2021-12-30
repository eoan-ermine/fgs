#pragma once

#include "llvm/IR/Value.h"
#include <memory>

namespace fgs::ast {

struct ASTNode {
	ASTNode* left;
	ASTNode* right;

	virtual ~ASTNode() { };
	virtual llvm::Value* codegen() = 0;
};

using ASTNodePtr = std::unique_ptr<ASTNode>;

}
