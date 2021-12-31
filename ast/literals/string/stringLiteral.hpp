#pragma once

#include <string>

#include "ast/node.hpp"
#include "llvm/IR/Constants.h"

namespace fgs::ast {

class StringLiteral: public ASTNode {
	std::string value;
public:
	llvm::Value* codegen() override;
	StringLiteral(const std::string&);
};

}