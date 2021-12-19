#pragma once

#include <string>
#include <variant>

#include "ast/node.hpp"

namespace fgs::ast {

struct FloatingConstant: public ASTNode {
	std::variant<float, double> value;

	FloatingConstant(float value);
	FloatingConstant(double value);
	FloatingConstant(long double value);
	
	llvm::Value* codegen() override;
};

FloatingConstant parseFloatingConstant(const std::string& number);

}
