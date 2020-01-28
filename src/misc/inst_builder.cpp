#include <ionir/misc/inst_builder.h>

namespace ionir {
    InstBuilder::InstBuilder(Ptr<Section> section) : section(section) {
        //
    }

    Ptr<Section> InstBuilder::getSection() const {
        return this->section;
    }

    void InstBuilder::insert(Ptr<Inst> inst) {
        this->section->getInsts().push_back(inst);
    }

    Ptr<AllocaInst> InstBuilder::createAlloca(std::string id, Ptr<Type> type) {
        Ptr<AllocaInst> allocaInst = this->make<AllocaInst>(AllocaInstOpts{
            this->section,
            id,
            type
        });

        this->section->insertInst(allocaInst);

        return allocaInst;
    }

    Ptr<BranchInst> InstBuilder::createBranch(Ptr<Expr<>> condition, PtrRef<Section> body, OptPtrRef<Section> otherwise) {
        return this->make<BranchInst>(BranchInstOpts{
            this->section,
            condition,
            body,
            otherwise
        });
    }

    Ptr<BranchInst> InstBuilder::createBranch(Ptr<Expr<>> condition, std::string id) {
        PtrRef<Section> body = std::make_shared<Ref<Section>>(id, nullptr);
        Ptr<BranchInst> branchInst = this->createBranch(condition, body);

        body->setOwner(branchInst);

        return branchInst;
    }

    Ptr<ReturnInst> InstBuilder::createReturn(OptPtr<Value<>> value) {
        return this->make<ReturnInst, ReturnInstOpts>(ReturnInstOpts{
            this->section,
            value
        });
    }

    Ptr<CallInst> InstBuilder::createCall(Ptr<Section> section, OptPtrRef<Function> callee, std::optional<std::string> yieldId) {
        return this->make<CallInst>(CallInstOpts{
            this->section,
            yieldId,
            callee
        });
    }
}
