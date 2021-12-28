#pragma once

namespace fgs::ast {

enum class CharacterType {
	SingleByte,
	UTF16,
	UTF32,
	Wide,
	Multicharacter
};

enum class CharacterFormatType {
	Hexadecimal,
	Octal,
	Decimal
};

class CharacterConstantType {
	CharacterType characterType;
	CharacterFormatType formatType;

	static CharacterType determineCharacterType(const std::string& character) {
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
	static CharacterFormatType determineCharacterFormatType(const std::string& character) {
		// without leading quote
		std::string trimmedCharacter = character.substr(1);

		if(trimmedCharacter.starts_with("\\x")) {
			return CharacterFormatType::Hexadecimal;
		} else if(trimmedCharacter.starts_with('\\')) {
			return CharacterFormatType::Octal;
		}
		return CharacterFormatType::Decimal;
	}
public:
	CharacterConstantType(const std::string& character): characterType{
		CharacterConstantType::determineCharacterType(character)
	}, formatType{
		CharacterConstantType::determineCharacterFormatType(character)
	} { }

	CharacterType getCharacterType() const {
		return characterType;
	}

	CharacterFormatType getFormatType() const {
		return formatType;
	}
};

}