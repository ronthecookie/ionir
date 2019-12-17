#include <iostream>
#include <memory>
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "code_gen/llvm_visitor.h"
#include "ast_constructs/binary_expr.h"
#include "ast_constructs/values/integer_kind.h"
#include "ast_constructs/values/integer.h"
#include "ast_constructs/insts/alloca.h"
#include "ast_constructs/insts/branch.h"
#include "ast_constructs/global_var.h"
#include "ast_constructs/function.h"
#include "ast_constructs/block.h"
#include "llvm/module.h"
#include "test_api/bootstrap.h"
#include "test_api/compare.h"
#include "constants/constants.h"
#include "pch.h"

using namespace ionir;

TEST(CodeGenTest, VisitExtern)
{
    Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();
    Ptr<Type> returnType = std::make_shared<Type>("void");
    Ptr<Args> args = std::make_shared<Args>();
    Ptr<Prototype> prototype = std::make_shared<Prototype>("testExtern", args, returnType);
    Ptr<Extern> externConstruct = std::make_shared<Extern>(prototype);

    visitor->visitExtern(externConstruct);

    Ptr<Module> module = std::make_shared<Module>(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "extern_simple"));
}

// TEST(CodeGenTest, VisitEmptyFunction)
// {
//     Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();
//     Ptr<Type> returnType = std::make_shared<Type>("void");
//     Ptr<Prototype> prototype = std::make_shared<Prototype>("foobar", new Args(), returnType);

//     Ptr<Block> body = std::make_shared<Block>({
//         std::make_shared<Section>(SectionKind::Entry, Const::sectionEntryId),
//     });

//     Ptr<Function> function = std::make_shared<Function>(prototype, body);

//     visitor->visitFunction(function);

//     EXPECT_TRUE(true);

//     // TODO
//     // Module *module = new Module(visitor->getModule());

//     // EXPECT_TRUE(test::compare::ir(module->getAsString(), "function_empty"));
// }

TEST(CodeGenTest, VisitEmptyGlobalVar)
{
    Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();

    // TODO: GlobalVar's type is hardcoded to double.
    Ptr<Type> type = std::make_shared<Type>("int", false);
    Ptr<GlobalVar> globalVar = std::make_shared<GlobalVar>(type, "test");

    visitor->visitGlobalVar(globalVar);

    Ptr<Module> module = std::make_shared<Module>(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "global_var_empty"));
}

TEST(CodeGenTest, VisitGlobalVar)
{
    Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();

    // TODO: GlobalVar's type is hardcoded to double.
    Ptr<Type> type = std::make_shared<Type>("int", false);
    Ptr<GlobalVar> globalVar = std::make_shared<GlobalVar>(type, "test", std::make_shared<IntegerValue>(IntegerKind::Int32, 123));

    visitor->visitGlobalVar(globalVar);

    Ptr<Module> module = std::make_shared<Module>(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "global_var"));
}

TEST(CodeGenTest, VisitAllocaInst)
{
    Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();
    Ptr<Function> function = test::bootstrap::emptyFunction();

    (*function->getBody()->getEntrySection())
        ->getInsts()
        .push_back(std::make_shared<AllocaInst>("foobar", std::make_shared<Type>("i32")));

    visitor->visitFunction(function);

    Ptr<Module> module = std::make_shared<Module>(visitor->getModule());

    EXPECT_TRUE(test::compare::ir(module->getAsString(), "inst_alloca"));
}

TEST(CodeGenTest, VisitBranchInst)
{
    Ptr<LlvmVisitor> visitor = test::bootstrap::llvmVisitor();
    Ptr<Function> function = test::bootstrap::emptyFunction();
    Ptr<Section> body = std::make_shared<Section>(SectionKind::Label, "ifbody");
    Ptr<BinaryExpr> condition = std::make_shared<BinaryExpr>(std::make_shared<BooleanValue>(true));

    (*function->getBody()->getEntrySection())
        ->getInsts()
        .push_back(std::make_shared<BranchInst>(condition, body));

    visitor->visitFunction(function);

    // Ptr<Module> module = std::make_shared<Module>(visitor->getModule());

    // module->print();

    // EXPECT_TRUE(test::compare::ir(module->getAsString(), "inst_alloca"));
}
