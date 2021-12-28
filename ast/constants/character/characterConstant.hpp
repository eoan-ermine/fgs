#pragma once

#include <string>
#include <variant>

#include "ast/node.hpp"

namespace fgs::ast {

class CharacterConstant: public ASTNode {
	int64_t getUniformValue() const;
	std::variant<int, char16_t, char32_t, wchar_t> value;
	int64_t uniformValue;
public:
	CharacterConstant(int value);
	CharacterConstant(char16_t value);
	CharacterConstant(char32_t value);
	CharacterConstant(wchar_t value);

	llvm::Value* codegen() override;
	static CharacterConstant parse(const std::string& character);
};

}
