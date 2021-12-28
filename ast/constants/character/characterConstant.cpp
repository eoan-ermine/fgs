#include <cstddef>
#include <string>
#include <sstream>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constants.h"

#include "characterConstant.hpp"
#include "characterConstantType.hpp"
#include "characterOffset.hpp"

#include "codegen/codegenState.hpp"

namespace fgs::ast {

CharacterConstant::CharacterConstant(int64_t value, CharacterConstantType type): 
	value{value}, type{type} { }

llvm::Value* CharacterConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
	return llvm::ConstantInt::getSigned(
		llvm::Type::getInt64Ty(codegenState.context),
		value
	);
}

CharacterConstant CharacterConstant::parse(const std::string& character) {
	auto type = CharacterConstantType(character);
	std::string extractedCharacter = extractCharacter(character, type);
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

	return CharacterConstant{internalRepresentation, type};
}

}
