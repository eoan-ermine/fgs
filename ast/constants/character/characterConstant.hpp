#pragma once

#include <string>
#include <variant>

#include "ast/node.hpp"
#include "characterConstantType.hpp"

namespace fgs::ast {

struct CharacterConstant: public ASTNode {
	std::variant<int, char16_t, char32_t, wchar_t> value;

	CharacterConstant(int value);
	CharacterConstant(char16_t value);
	CharacterConstant(char32_t value);
	CharacterConstant(wchar_t value);

	int64_t getUniformValue() const;
	llvm::Value* codegen() override;
};

CharacterConstant parseCharacterConstant(const std::string& character, CharacterConstantType type);

}
