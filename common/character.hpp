#pragma once

#include <string>
#include <string_view>

#include "llvm/ADT/APInt.h"

namespace fgs::common {

class Character {
	llvm::APInt value;
public:
	Character(const std::string& character);
	operator const llvm::APInt&() const;
};

}

namespace fgs::common::detail {

enum class CharacterType {
	SingleByte,
	UTF16,
	UTF32,
	Wide,
	Multicharacter
};

CharacterType determineCharacterType(std::string_view character);

enum class CharacterFormatType {
	Hexadecimal = 16,
	Octal = 8,
	Decimal = 10
};

CharacterFormatType determineCharacterFormatType(std::string_view character);

class CharacterConstantType {
	CharacterType characterType;
	CharacterFormatType formatType;
public:
	CharacterConstantType(std::string_view character);
	CharacterType getCharacterType() const;
	CharacterFormatType getFormatType() const;
};

class CharacterOffset {
	std::size_t left;
	std::size_t right;
public:
	CharacterOffset(std::string_view character, CharacterConstantType type);
	std::size_t getLeftBorder() const;
	std::size_t getRightBorder() const;
};

std::string extractCharacter(const std::string& character, CharacterConstantType type);

}