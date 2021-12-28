#include <cstddef>
#include <string>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constants.h"

#include "characterConstant.hpp"
#include "characterConstantType.hpp"
#include "utility.hpp"

#include "codegen/codegenState.hpp"

namespace fgs::ast {

CharacterConstant::CharacterConstant(int value): value{value}, uniformValue{getUniformValue()} { }
CharacterConstant::CharacterConstant(char16_t value): value{value}, uniformValue{getUniformValue()} { }
CharacterConstant::CharacterConstant(char32_t value): value{value}, uniformValue{getUniformValue()} { }
CharacterConstant::CharacterConstant(wchar_t value): value{value}, uniformValue{getUniformValue()} { }

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

CharacterConstant CharacterConstant::parse(const std::string& character) {
	auto type = CharacterConstantType(character);
	std::string extractedCharacter = extractCharacter(character, type);
	int64_t internalRepresentation = [&]() {
		switch(type.getFormatType()) {
			case FormatType::Hexadecimal:
				return std::stoi(extractedCharacter, nullptr, 16);
			case FormatType::Octal:
				return std::stoi(extractedCharacter, nullptr, 8);
			case FormatType::Decimal:
				return std::stoi(extractedCharacter, nullptr, 10);
		}
	}();

	switch(type.getCharacterType()) {
		case CharacterType::SingleByte:
			[[fallthrough]];
		case CharacterType::Multicharacter:
			return CharacterConstant(static_cast<int>(internalRepresentation));
			break;
		case CharacterType::UTF16:
			return CharacterConstant(static_cast<char16_t>(internalRepresentation));
			break;
		case CharacterType::UTF32:
			return CharacterConstant(static_cast<char32_t>(internalRepresentation));
			break;
		case CharacterType::Wide:
			return CharacterConstant(static_cast<wchar_t>(internalRepresentation));
			break;
	}
}

}
