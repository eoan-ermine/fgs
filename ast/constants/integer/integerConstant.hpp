#pragma once

#include <cstddef>
#include <string>
#include <string_view>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constants.h"

#include "ast/node.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

struct IntegerConstant: public ASTNode {
	int64_t value;

	IntegerConstant(int64_t value): value(value) { }
	llvm::Value* codegen() override {
		auto codegenState = fgs::codegen::CodegenState{};
		return llvm::ConstantInt::getSigned(
			llvm::Type::getInt64Ty(codegenState.context),
			value
		);
	}
};

IntegerConstant parseIntegerConstant(const std::string& number) {
	long long result = 0;

	if(number.starts_with("0b") || number.starts_with("0B")) {
		result = std::stoll(
			number.substr(2), nullptr, 2
		);
	} else if(number.starts_with("0x") || number.starts_with("0X")) {
		result = std::stoll(
			number.substr(2), nullptr, 16
		);
	} else if(number.starts_with("0")) {
		result = std::stoll(
			number.substr(1), nullptr, 16
		);
	} else {
		result = std::stoll(number, nullptr);
	}

	return IntegerConstant(static_cast<int64_t>(result));
}

}
