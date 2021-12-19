#pragma once

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

namespace fgs::codegen {

struct CodegenState {
	static llvm::LLVMContext context;
	static llvm::IRBuilder<> builder;
	static std::unique_ptr<llvm::Module> module;
};

}