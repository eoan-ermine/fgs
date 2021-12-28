#pragma once

namespace fgs::ast {

enum class CharacterType {
	SingleByte,
	UTF16,
	UTF32,
	Wide,
	Multicharacter
};

enum class FormatType {
	Hexadecimal,
	Octal,
	Decimal
};

class CharacterConstantType {
	CharacterType characterType;
	FormatType formatType;

	static CharacterType determineCharacterType(const std::string& character) {
		CharacterType type;
		constexpr size_t SINGLEBYTE_CHARACTER_LENGTH = 3;

		if(character.starts_with('u')) {
			type = CharacterType::UTF16;
		} else if(character.starts_with('U')) {
			type = CharacterType::UTF32;
		} else if(character.starts_with('L')) {
			type = CharacterType::Wide;
		} else if(character.size() == SINGLEBYTE_CHARACTER_LENGTH) {
			return CharacterType::SingleByte;
		}

		return CharacterType::Multicharacter;
	}
	static FormatType determineFormatType(const std::string& character) {
		FormatType type;

		if(character.starts_with("\\x")) {
			type = FormatType::Hexadecimal;
		} else if(character.starts_with('\\')) {
			type = FormatType::Octal;
		} else {
			type = FormatType::Decimal;
		}

		return type;
	}
public:
	CharacterConstantType(const std::string& character): characterType{
		CharacterConstantType::determineCharacterType(character)
	}, formatType{
		CharacterConstantType::determineFormatType(character)
	} { }

	CharacterType getCharacterType() const {
		return characterType;
	}

	FormatType getFormatType() const {
		return formatType;
	}
};

}