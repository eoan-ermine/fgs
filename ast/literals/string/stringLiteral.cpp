#include "stringLiteral.hpp"
#include "codegen/codegenState.hpp"

namespace fgs::ast {

llvm::Value* StringLiteral::codegen() {
	auto state = fgs::codegen::CodegenState{};
	return llvm::ConstantDataArray::getString(state.context, value);
}

StringLiteral::StringLiteral(const std::string& value): value(value) { }

}