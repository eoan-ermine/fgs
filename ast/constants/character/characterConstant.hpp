#pragma once

#include <string>

#include "ast/node.hpp"
#include "llvm/ADT/APInt.h"

namespace fgs::ast {

class CharacterConstant: public ASTNode {
	llvm::APInt value;
	CharacterConstant(llvm::APInt value);
public:
	llvm::Value* codegen() override;
	static CharacterConstant parse(const std::string& character);
};

}
