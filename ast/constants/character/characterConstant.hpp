#pragma once

#include <string>
#include <variant>

#include "ast/node.hpp"
#include "characterConstantType.hpp"

namespace fgs::ast {

class CharacterConstant: public ASTNode {
	int64_t value;
	CharacterConstantType type;
	CharacterConstant(int64_t value, CharacterConstantType type);
public:
	llvm::Value* codegen() override;
	static CharacterConstant parse(const std::string& character);
};

}
