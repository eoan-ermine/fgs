#pragma once

#include <string>

#include "ast/node.hpp"
#include "common/integer.hpp"

namespace fgs::ast {

class IntegerConstant: public ASTNode {
	::fgs::common::Integer value;
public:
	IntegerConstant(const std::string& integer);
	llvm::Value* codegen() override;
};

}
