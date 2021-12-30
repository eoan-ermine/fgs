#include <cstddef>
#include <string>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/DerivedTypes.h"
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
		llvm::Type::getInt64Ty(codegenState.context),
		value
	);
}

IntegerConstant IntegerConstant::parse(const std::string& number) {
	auto type = IntegerConstantType(number);
	std::string extractedInteger = extractInteger(number, type);
	return IntegerConstant(
		llvm::APInt(64, extractedInteger, static_cast<uint8_t>(type.getFormatType()))
	);
}

}
