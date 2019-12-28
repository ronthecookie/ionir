#include <ionir/syntax/driver.h>
#include <ionir/passes/pass_manager.h>

namespace ionir {
    PassManager::PassManager() : passes({}) {
        //
    }

    void PassManager::registerPass(Ptr<PassManagerItem> item) {
        this->passes.push_back(item);
    }

    void PassManager::run(Ast ast) {
        for (auto item : this->passes) {
            // TODO: Process priorities.
            for (auto topLevelConstruct : ast) {
                item->pass->visit(topLevelConstruct);
            }
        }
    }
}
