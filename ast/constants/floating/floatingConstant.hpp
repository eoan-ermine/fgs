#pragma once

#include <string>

#include "ast/node.hpp"
#include "common/floating.hpp"

namespace fgs::ast {

class FloatingConstant: public ASTNode {
	::fgs::common::Floating value;
public:
	FloatingConstant(const std::string& value);
	llvm::Value* codegen() override;
};

}
