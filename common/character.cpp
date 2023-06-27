#include <sstream>

#include "character.hpp"

namespace fgs::common {

Character::Character(const std::string& character) {
	using namespace detail;

	auto type = CharacterConstantType(character);
	std::string extractedCharacter = detail::extractCharacter(character, type);
	int64_t internalRepresentation = [&]() {
		std::istringstream stream{extractedCharacter};
		int64_t result;

		switch(type.getFormatType()) {
			case CharacterFormatType::Hexadecimal:
				stream >> std::hex >> result;
			case CharacterFormatType::Octal:
				stream >> std::oct >> result;
			case CharacterFormatType::Decimal:
				stream >> result;
		}

		return result;
	}();

	value = llvm::APInt(64, internalRepresentation);
}

Character::operator const llvm::APInt&() const {
	return value;
}

}

namespace fgs::common::detail {

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

CharacterFormatType determineCharacterFormatType(std::string_view character) {
	// ' is leading quote
	if(character.starts_with("'\\x")) {
		return CharacterFormatType::Hexadecimal;
	} else if(character.starts_with("'\\")) {
		return CharacterFormatType::Octal;
	}
	return CharacterFormatType::Decimal;
}

CharacterConstantType::CharacterConstantType(std::string_view character): characterType{
	determineCharacterType(character)
}, formatType{
	determineCharacterFormatType(character)
} { }

CharacterType CharacterConstantType::getCharacterType() const {
	return characterType;
}

CharacterFormatType CharacterConstantType::getFormatType() const {
	return formatType;
}

CharacterOffset::CharacterOffset(std::string_view character, CharacterConstantType type): left{1}, right{character.size() - 1} {
	// left = 1 and right = character.size() - 1 because of leading and closing quotes

	switch(type.getCharacterType()) {
		case CharacterType::UTF16:
		case CharacterType::UTF32:
		case CharacterType::Wide:
			left += 1;
	}

	// there are no octal 'cause we can ignore leading zero
	switch(type.getFormatType()) {
		case CharacterFormatType::Hexadecimal:
			left += 2;
			break;
	}
}

std::size_t CharacterOffset::getLeftBorder() const {
	return left;
}

std::size_t CharacterOffset::getRightBorder() const {
	return right;
}

std::string extractCharacter(const std::string& character, CharacterConstantType type) {
	CharacterOffset offset{character, type};
	return character.substr(offset.getLeftBorder(), offset.getRightBorder());
}

}