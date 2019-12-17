#include "constructs/inst_kind.h"
#include "passes/pass.h"
#include "call.h"

namespace ionir
{
CallInst::CallInst(Ptr<Scope> scope, std::string target, std::optional<Ptr<Function>> callee)
    : PartialInst<Ptr<Function>>(InstKind::Goto, scope, callee), target(target)
{
    if (callee.has_value())
    {
        this->resolve(*callee);
    }
}

Ptr<Construct> CallInst::accept(Pass *visitor)
{
    return visitor->visitGotoInst(this->cast<GotoInst>());
}

std::string CallInst::getTarget() const
{
    return this->target;
}

void CallInst::setTarget(std::string target)
{
    this->target = target;
}

std::optional<Ptr<Function>> CallInst::getCallee() const
{
    return this->getValue();
}

void CallInst::setCallee(Ptr<Function> callee)
{
    this->resolve(callee);
}
} // namespace ionir