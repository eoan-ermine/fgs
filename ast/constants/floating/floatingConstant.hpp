#pragma once

#include <string>
#include <variant>

#include "ast/node.hpp"
#include "floatingConstantType.hpp"

namespace fgs::ast {

class FloatingConstant: public ASTNode {
	double value;
	FloatingConstantType type;
	FloatingConstant(double value, FloatingConstantType type);
public:
	llvm::Value* codegen() override;
	static FloatingConstant parse(const std::string& number);
};

}
