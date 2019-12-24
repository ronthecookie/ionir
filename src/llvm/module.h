#pragma once

#include <string>
#include <llvm/IR/Module.h>
#include "misc/wrapper.h"
#include "context.h"

namespace ionir
{
class Module : public Wrapper<llvm::Module *>
{
protected:
    Context *context;

public:
    Module(llvm::Module *module, Context *context);

    explicit Module(llvm::Module *module);

    ~Module();

    Context *getContext() const;

    std::string getAsString() const;

    void print();

    void printToLlvmErrs() const;
};
} // namespace ionir
