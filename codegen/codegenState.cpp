#include "codegenState.hpp"

#include <memory>

using namespace llvm;

namespace fgs::codegen {

LLVMContext CodegenState::context;
IRBuilder<> CodegenState::builder(context);
std::unique_ptr<Module> CodegenState::module;

}
