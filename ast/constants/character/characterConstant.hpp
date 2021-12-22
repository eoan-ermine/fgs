#pragma once

#include <string>
#include <variant>

#include "ast/node.hpp"
#include "characterConstantType.hpp"

namespace fgs::ast {

class CharacterConstant: public ASTNode {
	std::variant<int, char16_t, char32_t, wchar_t> value;
	static CharacterConstantType determineCharacterType(const std::string& character);
public:
	CharacterConstant(int value);
	CharacterConstant(char16_t value);
	CharacterConstant(char32_t value);
	CharacterConstant(wchar_t value);

	int64_t getUniformValue() const;
	llvm::Value* codegen() override;

	static CharacterConstant parse(const std::string& character);
};

}
