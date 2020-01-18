#pragma once

#include <optional>
#include <ionir/misc/helpers.h>
#include <ionir/passes/pass.h>
#include <ionir/reporting/notice.h>
#include <ionir/tracking/scope.h>

namespace ionir {
    /**
     * Resolves partial constructs which reference
     * undefined symbols at the time by their identifier(s).
     */
    class NameResolutionPass : public Pass {
    private:
        Ptr<StackTrace> stackTrace;

        ScopeStack scopeStack;

    public:
        NameResolutionPass(Ptr<StackTrace> stackTrace = std::make_shared<StackTrace>());

        void visitModule(Ptr<Module> node) override {
            this->scopeStack.push(node->getSymbolTable());
        }

        void visitRef(PtrRef<> node) override;

        Ptr<StackTrace> getStackTrace() const;

        const ScopeStack &getScopeStack() const;
    };
}