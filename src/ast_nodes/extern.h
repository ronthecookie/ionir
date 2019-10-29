#pragma once

#include "code_gen/node.h"
#include "code_gen/node_type.h"
#include "ast_nodes/prototype.h"

namespace ionir
{
class Extern : public Node
{
private:
	Prototype prototype;

public:
	Extern(Prototype prototype) : Node(NodeType::Extern), prototype(prototype)
	{
		this->prototype = prototype;
	}

	Prototype getPrototype() const
	{
		return this->prototype;
	}
};
} // namespace ionir