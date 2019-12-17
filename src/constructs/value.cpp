#include "code_gen/node_kind.h"
#include "passes/pass.h"
#include "value.h"

namespace ionir
{
Value::Value(ValueKind kind) : Construct(ConstructKind::Value), kind(kind)
{
    //
}

Ptr<Construct> Value::accept(Pass *visitor)
{
    return visitor->visitValue(this->cast<Value>());
}

ValueKind Value::getValueKind() const
{
    return this->kind;
}
} // namespace ionir