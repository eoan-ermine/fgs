#pragma once

#include <cstddef>
#include <string>

#include "ast/node.hpp"

namespace fgs::ast {

class IntegerConstant: public ASTNode {
	int64_t value;
public:
	IntegerConstant(int64_t value);
	
	llvm::Value* codegen() override;

	static IntegerConstant parse(const std::string& number);
};

}
