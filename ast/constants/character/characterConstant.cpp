#include <string>

#include "llvm/IR/Constants.h"

#include "characterConstant.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

CharacterConstant::CharacterConstant(const std::string& character): value{character} { }

llvm::Value* CharacterConstant::codegen() {
	auto codegenState = fgs::codegen::CodegenState{};
	return llvm::ConstantInt::get(
		codegenState.context, value
	);
}

}
