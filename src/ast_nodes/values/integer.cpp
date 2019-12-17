#include "passes/pass.h"
#include "ast_constructs/value_kind.h"
#include "integer.h"

namespace ionir
{
IntegerValue::IntegerValue(IntegerKind kind, long value)
    : Value(ValueKind::Integer), kind(kind), value(value)
{
    //
}

Ptr<Construct> IntegerValue::accept(Pass *visitor)
{
    return visitor->visitIntegerValue(this->cast<IntegerValue>());
}

IntegerKind IntegerValue::getIntKind() const
{
    return this->kind;
}

long IntegerValue::getValue() const
{
    return this->value;
}

void IntegerValue::setValue(long value)
{
    this->value = value;
}
} // namespace ionir
