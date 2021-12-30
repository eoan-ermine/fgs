#include <string>

#include "llvm/IR/Constants.h"

#include "floatingConstant.hpp"
#include "floatingConstantType.hpp"
#include "floatingOffset.hpp"

#include "codegen/codegenState.hpp"

namespace fgs::ast {

FloatingConstant::FloatingConstant(llvm::APFloat value): value(value) { }

llvm::Value* FloatingConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
    return llvm::ConstantFP::get(codegenState.context, value);
}

ASTNodePtr FloatingConstant::parse(const std::string& number) {
	auto type = FloatingConstantType(number);
	auto extractedNumber = extractFloating(number, type);
	
	auto value = [&]() {
		switch(type.getFloatingType()) {
			case FloatingType::Float:
				return llvm::APFloat(llvm::APFloat::IEEEsingle(), extractedNumber);
			case FloatingType::Double:
				return llvm::APFloat(llvm::APFloat::IEEEdouble(), extractedNumber);
			case FloatingType::LongDouble:
				return llvm::APFloat(llvm::APFloat::x87DoubleExtended(), extractedNumber);
		}
	}();
	
	return ASTNodePtr{new FloatingConstant{value}};
}

}
