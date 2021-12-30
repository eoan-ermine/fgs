#include <string>

#include "llvm/IR/Constants.h"

#include "integerConstant.hpp"
#include "integerConstantType.hpp"
#include "integerOffset.hpp"

#include "codegen/codegenState.hpp"

namespace fgs::ast {

IntegerConstant::IntegerConstant(llvm::APInt value): value(value) { }
llvm::Value* IntegerConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
	return llvm::ConstantInt::get(
		codegenState.context, value
	);
}

ASTNodePtr IntegerConstant::parse(const std::string& number) {
	auto type = IntegerConstantType(number);
	std::string extractedInteger = extractInteger(number, type);
	llvm::APInt value = llvm::APInt(64, extractedInteger, static_cast<uint8_t>(type.getFormatType()));

	unsigned bitWidth = value.ceilLogBase2();

	if(bitWidth <= 16) bitWidth = 16;
	else if(bitWidth <= 32) bitWidth = 32;
	value = value.trunc(bitWidth);

	return ASTNodePtr{new IntegerConstant(value)};
}

}
