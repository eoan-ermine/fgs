#include <cstddef>
#include <string>
#include <sstream>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/DerivedTypes.h"
#include <string>

#include "llvm/IR/Constants.h"

#include "characterConstant.hpp"
#include "characterConstantType.hpp"
#include "characterOffset.hpp"

#include "codegen/codegenState.hpp"

namespace fgs::ast {

CharacterConstant::CharacterConstant(llvm::APInt value): value{value} { }

llvm::Value* CharacterConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
	return llvm::ConstantInt::get(
		codegenState.context, value
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

	return CharacterConstant{llvm::APInt(64, internalRepresentation)};
}

}
