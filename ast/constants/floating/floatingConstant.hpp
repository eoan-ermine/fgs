#pragma once

#include <string>

#include "ast/node.hpp"

namespace fgs::ast {

struct FloatingConstant: public ASTNode {
	double value;
	FloatingConstant(double value);
	llvm::Value* codegen() override;
};

FloatingConstant parseFloatingConstant(const std::string& number);

}
