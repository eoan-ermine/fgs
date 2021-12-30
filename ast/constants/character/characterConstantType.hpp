#pragma once

#include <string_view>

namespace fgs::ast {

enum class CharacterType {
	SingleByte,
	UTF16,
	UTF32,
	Wide,
	Multicharacter
};

CharacterType determineCharacterType(std::string_view character) {
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

CharacterFormatType determineCharacterFormatType(std::string_view character) {
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
	CharacterConstantType(std::string_view character): characterType{
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