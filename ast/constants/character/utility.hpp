#pragma once

#include "characterConstantType.hpp"

namespace fgs::ast {

class CharacterOffset {
	std::size_t left;
	std::size_t right;
public:
	CharacterOffset(const std::string& character, CharacterConstantType type): left{1}, right{character.size() - 1} {
		switch(type.getCharacterType()) {
			case CharacterType::UTF16:
			case CharacterType::UTF32:
			case CharacterType::Wide:
				left += 1;
		}
		switch(type.getFormatType()) {
			case FormatType::Hexadecimal:
				left += 2;
				break;
			case FormatType::Octal:
				left += 1;
				break;
		}
	}

	std::size_t getLeftBorder() const {
		return left;
	}

	std::size_t getRightBorder() const {
		return right;
	}
};

std::string extractCharacter(const std::string& character, CharacterConstantType type) {
	CharacterOffset offset{character, type};
	return character.substr(offset.getLeftBorder(), offset.getRightBorder());
}

}