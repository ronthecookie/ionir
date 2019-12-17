#include "passes/pass.h"
#include "constructs/value_kind.h"
#include "boolean.h"

namespace ionir
{
BooleanValue::BooleanValue(bool value)
    : Value(ValueKind::Boolean), value(value)
{
    //
}

Ptr<Construct> BooleanValue::accept(Pass *visitor)
{
    return visitor->visitBooleanValue(this->cast<BooleanValue>());
}

bool BooleanValue::getValue() const
{
    return this->value;
}

void BooleanValue::setValue(bool value)
{
    this->value = value;
}
} // namespace ionir