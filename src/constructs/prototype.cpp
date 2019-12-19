#include "constructs/construct_kind.h"
#include "passes/pass.h"
#include "prototype.h"

namespace ionir
{
Prototype::Prototype(std::string id, Ptr<Args> args, Ptr<Type> returnType)
    : Construct(ConstructKind::Prototype), id(id), args(args), returnType(returnType)
{
    //
}

void Prototype::accept(Pass *visitor)
{
    visitor->visitPrototype(this->cast<Prototype>());
}

std::string Prototype::getId() const
{
    return this->id;
}

Ptr<Args> Prototype::getArgs() const
{
    return this->args;
}

Ptr<Type> Prototype::getReturnType() const
{
    return this->returnType;
}
} // namespace ionir
