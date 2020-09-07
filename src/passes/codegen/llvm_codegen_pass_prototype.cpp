#include <llvm/ADT/APInt.h>
#include <llvm/IR/DerivedTypes.h>
#include <ionir/construct/value.h>
#include <ionir/passes/codegen/llvm_codegen_pass.h>

namespace ionir {
    void LlvmCodegenPass::visit(ionshared::Ptr<Construct> node) {
        /**
         * Only instruct the node to visit this instance and
         * not its children, since they're already visited by
         * the other member methods.
         */
        node->accept(*this);
    }

    void LlvmCodegenPass::visitExtern(ionshared::Ptr<Extern> node) {
        this->requireModule();

        if (node->getPrototype() == nullptr) {
            throw std::runtime_error("Unexpected external definition's prototype to be null");
        }
        else if ((*this->llvmModuleBuffer)->getFunction(node->getPrototype()->getId()) != nullptr) {
            throw std::runtime_error("Re-definition of extern not allowed");
        }

        // Visit the prototype.
        this->visitPrototype(node->getPrototype());

        // No need to push the resulting function onto the stack.
    }

    void LlvmCodegenPass::visitPrototype(ionshared::Ptr<Prototype> node) {
        this->requireModule();
        this->requireContext();

        auto argsMap = node->getArgs()->getItems();
        auto &argsNativeMap = argsMap->unwrapConst();

        // Retrieve argument count from the argument vector.
        uint32_t argumentCount = argsMap->getSize();

        // Create the argument buffer vector.
        std::vector<llvm::Type *> llvmArgumentTypes = {};

        // Attempt to retrieve an existing function.
        llvm::Function *llvmFunction = (*this->llvmModuleBuffer)->getFunction(node->getId());

        // A function with a matching identifier already exists.
        if (llvmFunction != nullptr) {
            // Function already has a body, disallow re-definition.
            if (llvmFunction->getBasicBlockList().empty()) {
                throw std::runtime_error("Cannot re-define function");
            }
                // If the function takes a different number of arguments, reject.
            else if (llvmFunction->arg_size() != argumentCount) {
                throw std::runtime_error("Re-definition of function with a different amount arguments");
            }
        }
        // Otherwise, function will be created.
        else {
            for (const auto &[id, arg] : argsNativeMap) {
                this->visitType(arg.first);
                llvmArgumentTypes.push_back(this->typeStack.pop());
            }

            // Visit and pop the return type.
            this->visitType(node->getReturnType());

            llvm::Type *llvmReturnType = this->typeStack.pop();

            // TODO: Support for infinite arguments and hard-coded return type.
            // Create the function type.
            llvm::FunctionType *llvmFunctionType = llvm::FunctionType::get(
                llvmReturnType,
                llvmArgumentTypes,
                node->getArgs()->getIsVariable()
            );

            // Cast the value to a function, since we know getCallee() will return a function.
            llvmFunction = llvm::dyn_cast<llvm::Function>(
                (*this->llvmModuleBuffer)->getOrInsertFunction(node->getId(), llvmFunctionType).getCallee()
            );

            // Set the function's linkage.
            llvmFunction->setLinkage(llvm::GlobalValue::LinkageTypes::ExternalLinkage);
        }

        // Begin processing arguments. Argument count must be the same.
        if (argumentCount != llvmFunction->arg_size()) {
            throw std::runtime_error("Expected argument count to be the same as the function's argument count");
        }

        int argCounter = 0;
        int llvmArgCounter = 0;

        // TODO: Simplify method of naming LLVM arguments, as this implementation is inefficient.
        for (const auto &[id, arg] : argsNativeMap) {
            for (auto &llvmArgument : llvmFunction->args()) {
                if (llvmArgCounter == argCounter) {
                    llvmArgument.setName(id);
                    llvmArgCounter = 0;

                    break;
                }

                llvmArgCounter++;
            }

            argCounter++;
        }

        this->valueStack.push(llvmFunction);
    }

    void LlvmCodegenPass::visitFunction(ionshared::Ptr<Function> node) {
        this->requireModule();

        if (!node->verify()) {
            throw std::runtime_error("Function verification failed");
        }
        else if ((*this->llvmModuleBuffer)->getFunction(node->getPrototype()->getId()) != nullptr) {
            throw std::runtime_error("A function with the same identifier has been already previously defined");
        }

        // Clear named values.
        this->namedValues.clear();

        // Visit the prototype.
        this->visitPrototype(node->getPrototype());

        // Retrieve the resulting function off the stack.
        llvm::Function *llvmFunction = this->valueStack.popAs<llvm::Function>();

        // Set the function buffer.
        this->llvmFunctionBuffer = llvmFunction;

        // Visiting the function body's yields no value to the value stack.
        this->visitFunctionBody(node->getBody());

        // TODO: Verify the resulting LLVM function (through LLVM)?

        this->valueStack.push(llvmFunction);
    }
}
