#pragma once

#include <memory>
#include <optional>
#include <stack>
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "code_gen/node.h"
#include "code_gen/node_kind.h"
#include "constructs/values/integer.h"
#include "constructs/values/char.h"
#include "constructs/values/string.h"
#include "constructs/type.h"
#include "constructs/block.h"
#include "constructs/binary_expr.h"
#include "constructs/function.h"
#include "constructs/extern.h"
#include "constructs/prototype.h"
#include "constructs/global_var.h"
#include "constructs/inst.h"
#include "constructs/insts/branch.h"
#include "constructs/insts/alloca.h"
#include "constructs/insts/return.h"
#include "misc/stack.h"
#include "misc/helpers.h"
#include "passes/pass.h"

namespace ionir
{
class LlvmVisitor : public Pass
{
protected:
	llvm::LLVMContext *context;

	llvm::Module *module;

	Stack<llvm::Value *> valueStack;

	Stack<llvm::Type *> typeStack;

	std::optional<llvm::Function *> function;

	std::optional<llvm::IRBuilder<>> builder;

	std::map<std::string, llvm::Value *> namedValues;

	/**
	 * Ensures that the builder is instantiated, otherwise
	 * throws a runtime error.
	 */
	void requireBuilder();

	void requireFunction();

public:
	LlvmVisitor(llvm::Module *module);

	~LlvmVisitor();

	llvm::Module *getModule() const;

	Stack<llvm::Value *> getValueStack() const;

	Stack<llvm::Type *> getTypeStack() const;

	Ptr<Construct> visitFunction(Ptr<Function> node) override;

	Ptr<Construct> visitExtern(Ptr<Extern> node) override;

	Ptr<Construct> visitSection(Ptr<Section> node) override;

	Ptr<Construct> visitBlock(Ptr<Block> node) override;

	Ptr<Construct> visitType(Ptr<Type> node) override;

	Ptr<Construct> visitBinaryExpr(Ptr<BinaryExpr> node) override;

	Ptr<Construct> visitPrototype(Ptr<Prototype> node) override;

	Ptr<Construct> visitIntegerValue(Ptr<IntegerValue> node) override;

	Ptr<Construct> visitCharValue(Ptr<CharValue> node) override;

	Ptr<Construct> visitStringValue(Ptr<StringValue> node) override;

	Ptr<Construct> visitAllocaInst(Ptr<AllocaInst> node) override;

	Ptr<Construct> visitReturnInst(Ptr<ReturnInst> node) override;

	Ptr<Construct> visitBranchInst(Ptr<BranchInst> node) override;

	Ptr<Construct> visitGlobalVar(Ptr<GlobalVar> node) override;
};
} // namespace ionir
