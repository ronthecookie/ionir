#pragma once

#include <optional>
#include <string>
#include <ionir/misc/helpers.h>
#include "values/value.h"
#include "construct.h"
#include "type.h"

namespace ionir {
    class Pass;

    class Global : public Construct {
    protected:
        Ptr <Type> type;

        std::string id;

        std::optional<Ptr < Value>> value;

    public:
        Global(Ptr <Type> type, std::string id, std::optional<Ptr < Value>>

        value = std::nullopt);

        void accept(Pass *visitor) override;

        Ptr <Type> getType() const;

        void setType(Ptr <Type> type);

        std::string getId() const;

        void setId(std::string id);

        std::optional<Ptr < Value>> getValue() const;

        void setValue(std::optional<Ptr < Value>>

        value);
    };
}