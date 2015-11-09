#include "llvm.h"
#include <iostream>
#include <functional>

using namespace llvm;

llvm::Module* makeLLVMModule();

void * compile(llvm::Module * m) {
    ExecutionEngine * engine =
      EngineBuilder(std::unique_ptr<Module>(m))
      .create();
    engine->finalizeObject();

    return engine->getPointerToFunction(
        m->getFunction("aFun"));
}

llvm::Module* makeLLVMModule() {
  Module* mod = new Module("mod", getGlobalContext());

  FunctionType* fTy = FunctionType::get(
      IntegerType::get(mod->getContext(), 32),
      {IntegerType::get(mod->getContext(), 32)},
      false);
  Function* fun = Function::Create(
      fTy,
      GlobalValue::ExternalLinkage,
      "aFun",
      mod);

  Function::arg_iterator args = fun->arg_begin();
  Value* int32_n = args++;
  int32_n->setName("n");

  BasicBlock* b = BasicBlock::Create(mod->getContext(),"entry",fun,0);

  ReturnInst::Create(mod->getContext(), int32_n, b);

  return mod;
}

int main() {
    // initialize the JIT
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeAsmParser();

    auto m = makeLLVMModule();
    auto f = compile(m);

    int res = ((int(*)(int))f)(22);

    std::cout << "Result : " << res << "\n";

    return 0;
}
