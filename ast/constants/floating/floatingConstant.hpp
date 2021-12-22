#pragma once

#include <string>
#include <variant>

#include "ast/node.hpp"

namespace fgs::ast {

class FloatingConstant: public ASTNode {
	std::variant<float, double> value;
public:
	FloatingConstant(float value);
	FloatingConstant(double value);
	FloatingConstant(long double value);
	
	llvm::Value* codegen() override;

	static FloatingConstant parse(const std::string& number);
};

}
