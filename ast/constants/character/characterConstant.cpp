#include <cstddef>
#include <string>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constants.h"

#include "characterConstant.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

CharacterConstant::CharacterConstant(int value): value{value} { }
CharacterConstant::CharacterConstant(char16_t value): value{value} { }
CharacterConstant::CharacterConstant(char32_t value): value{value} { }
CharacterConstant::CharacterConstant(wchar_t value): value{value} { }

int64_t CharacterConstant::getUniformValue() const {
	int64_t convertedValue{};

	if(const int* val = std::get_if<int>(&value)) {
		convertedValue = static_cast<int64_t>(*val);
	} else if(const char16_t* val = std::get_if<char16_t>(&value)) {
		convertedValue = static_cast<int64_t>(*val);
	} else if(const char32_t* val = std::get_if<char32_t>(&value)) {
		convertedValue = static_cast<int64_t>(*val);
	} else if(const wchar_t* val = std::get_if<wchar_t>(&value)) {
		convertedValue = static_cast<int64_t>(*val);
	}

	return convertedValue;
}

llvm::Value* CharacterConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
	return llvm::ConstantInt::getSigned(
		llvm::Type::getInt64Ty(codegenState.context),
		getUniformValue()
	);
}

CharacterConstantType CharacterConstant::determineCharacterType(const std::string& character) {
	CharacterConstantType type;
	constexpr size_t SINGLEBYTE_CHARACTER_LENGTH = 3;

	if(character.starts_with('u')) {
		type = CharacterConstantType::UTF16;
	} else if(character.starts_with('U')) {
		type = CharacterConstantType::UTF32;
	} else if(character.starts_with('L')) {
		type = CharacterConstantType::Wide;
	} else if(character.size() == SINGLEBYTE_CHARACTER_LENGTH) {
		return CharacterConstantType::SingleByte;
	}

	return CharacterConstantType::Multicharacter;
}

CharacterConstant CharacterConstant::parse(const std::string& character) {
	std::size_t leftBorder = 0;
	std::size_t rightBorder = character.size() - 1;

	CharacterConstantType type = CharacterConstant::determineCharacterType(character);
	if(type != CharacterConstantType::SingleByte || type != CharacterConstantType::Multicharacter) {
		leftBorder += 1;
	}

	int64_t internalRepresentation = 0;
	if(character.starts_with("\\u") || character.starts_with("\\U")) {
		leftBorder += 2;
		internalRepresentation = std::stoi(character.substr(leftBorder, rightBorder), nullptr, 16);
	} else if(character.starts_with("\\")) {
		leftBorder += 1;
		internalRepresentation = std::stoi(character.substr(leftBorder, rightBorder), nullptr, 8);
	} else {
		internalRepresentation = std::stoi(character.substr(leftBorder, rightBorder), nullptr, 10);
	}

	switch(type) {
		case CharacterConstantType::SingleByte:
			[[fallthrough]];
		case CharacterConstantType::Multicharacter:
			return CharacterConstant(static_cast<int>(internalRepresentation));
			break;
		case CharacterConstantType::UTF16:
			return CharacterConstant(static_cast<char16_t>(internalRepresentation));
			break;
		case CharacterConstantType::UTF32:
			return CharacterConstant(static_cast<char32_t>(internalRepresentation));
			break;
		case CharacterConstantType::Wide:
			return CharacterConstant(static_cast<wchar_t>(internalRepresentation));
			break;
	}
}

}
