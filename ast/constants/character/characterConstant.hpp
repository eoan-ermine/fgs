#pragma once

#include <string>

#include "ast/node.hpp"
#include "common/character.hpp"

namespace fgs::ast {

class CharacterConstant: public ASTNode {
	::fgs::common::Character value;
public:
	CharacterConstant(const std::string& character);
	llvm::Value* codegen() override;
};

}
