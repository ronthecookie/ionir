#pragma once

#include "code_gen/llvm_visitor.h"
#include "code_gen/node.h"
#include "code_gen/node_kind.h"

namespace ionir
{
class Type : public Node
{
protected:
    bool isPointer;

public:
    Type(bool isPointer) : Node(NodeKind::Type)
    {
        this->isPointer = isPointer;
    }

    Node* accept(LlvmVisitor *visitor) override
    {
        return visitor->visitType(this);
    }

    bool getIsPointer() const
    {
        return this->isPointer;
    }
};
} // namespace ionir
