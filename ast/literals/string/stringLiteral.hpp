#pragma once

#include <string>

#include "ast/node.hpp"
#include "llvm/IR/Constants.h"

namespace fgs::ast {

class StringLiteral: public ASTNode {
	std::string value;
	StringLiteral(std::string);
public:
	llvm::Value* codegen() override;
	ASTNodePtr parse(const std::string&);
};

}