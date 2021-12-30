#include "stringLiteral.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

StringLiteral::StringLiteral(std::string value): value(value) { }
llvm::Value* StringLiteral::codegen() {
	auto state = fgs::codegen::CodegenState{};
	return llvm::ConstantDataArray::getString(state.context, value);
}

ASTNodePtr StringLiteral::parse(const std::string& literal) {
	return ASTNodePtr{new StringLiteral{literal}};
}

}