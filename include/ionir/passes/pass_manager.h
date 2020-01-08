#pragma once

#include <vector>
#include <ionir/syntax/ast.h>
#include <ionir/misc/helpers.h>

namespace ionir {
    enum class PassPriority {
        /**
         * Highest priority. This precedence
         * will be executed first.
         */
            Important,

        Normal,

        Low,

        Lowest
    };

    struct PassManagerItem {
        Ptr<Pass> pass;

        PassPriority priority = PassPriority::Normal;
    };

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
