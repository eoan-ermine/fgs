#pragma once

#include <string>

#include "ast/node.hpp"
#include "llvm/ADT/APFloat.h"

namespace fgs::ast {

class FloatingConstant: public ASTNode {
	llvm::APFloat value;
	FloatingConstant(llvm::APFloat value);
public:
	llvm::Value* codegen() override;
	static ASTNodePtr parse(const std::string& number);
};

}
