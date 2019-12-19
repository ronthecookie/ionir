#pragma once

#include <optional>
#include "syntax/token_type.h"
#include "misc/helpers.h"
#include "expr.h"

namespace ionir
{
class Pass;

class IdExpr : public Expr
{
public:
    IdExpr();

    Ptr<Construct> accept(Pass *visitor) override;
};
} // namespace ionir
