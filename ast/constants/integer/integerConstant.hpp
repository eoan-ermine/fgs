#pragma once

#include <string>

#include "ast/node.hpp"
#include "llvm/ADT/APInt.h"

namespace fgs::ast {

class IntegerConstant: public ASTNode {
	llvm::APInt value;
	IntegerConstant(llvm::APInt value);
public:
	llvm::Value* codegen() override;
	static ASTNodePtr parse(const std::string& number);
};

}
