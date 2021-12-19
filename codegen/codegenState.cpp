#include "codegenState.hpp"

#include <memory>

using namespace llvm;

LLVMContext CodegenState::context;
IRBuilder<> CodegenState::builder(context);
std::unique_ptr<Module> CodegenState::module;
