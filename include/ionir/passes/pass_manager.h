#pragma once

#include <vector>
#include <ionir/syntax/ast.h>
#include <ionir/misc/helpers.h>
#include "pass_manager_item.h"

namespace ionir {
    class PassManager {
    protected:
        /**
         * Internal container on which pass
         * manager items will be both stored
         * and processed from.
         */
        std::vector<PassManagerItem> passes;

    public:
        explicit PassManager(std::vector<PassManagerItem> passes = {});

        std::vector<PassManagerItem> &getPasses();

        void setPasses(std::vector<PassManagerItem> passes);

        /**
         * Register a pass in the set. Returns whether
         * the provided pass was successfully registered
         * in the internal set.
         */
        void registerPass(PassManagerItem item);

        void registerPass(Ptr<Pass> pass);

        void run(Ast ast);
    };
}
