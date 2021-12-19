#pragma once

#include <cstddef>
#include <string>

#include "ast/node.hpp"

namespace fgs::ast {

struct IntegerConstant: public ASTNode {
	int64_t value;
	IntegerConstant(int64_t value);
	llvm::Value* codegen() override;
};

IntegerConstant parseIntegerConstant(const std::string& number);

}
