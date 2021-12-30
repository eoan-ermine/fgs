#pragma once

#include <string>

namespace fgs::ast {

enum class CharacterType {
	SingleByte,
	UTF16,
	UTF32,
	Wide,
	Multicharacter
};

CharacterType determineCharacterType(const std::string& character) {
	constexpr size_t SINGLEBYTE_CHARACTER_LENGTH = 3;

	if(character.starts_with('u')) {
		return CharacterType::UTF16;
	} else if(character.starts_with('U')) {
		return CharacterType::UTF32;
	} else if(character.starts_with('L')) {
		return CharacterType::Wide;
	} else if(character.size() == SINGLEBYTE_CHARACTER_LENGTH) {
		return CharacterType::SingleByte;
	}

	return CharacterType::Multicharacter;
}

enum class CharacterFormatType {
	Hexadecimal = 16,
	Octal = 8,
	Decimal = 10
};

CharacterFormatType determineCharacterFormatType(const std::string& character) {
	// ' is leading quote
	if(character.starts_with("'\\x")) {
		return CharacterFormatType::Hexadecimal;
	} else if(character.starts_with("'\\")) {
		return CharacterFormatType::Octal;
	}
	return CharacterFormatType::Decimal;
}

class CharacterConstantType {
	CharacterType characterType;
	CharacterFormatType formatType;
public:
	CharacterConstantType(const std::string& character): characterType{
		determineCharacterType(character)
	}, formatType{
		determineCharacterFormatType(character)
	} { }

	CharacterType getCharacterType() const {
		return characterType;
	}

	CharacterFormatType getFormatType() const {
		return formatType;
	}
};

}