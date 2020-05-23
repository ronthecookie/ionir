#include <ionir/passes/pass.h>

namespace ionir {
    StoreInst::StoreInst(StoreInstOpts opts)
        : Inst(opts.parent, InstKind::Store), value(opts.value), target(opts.target) {
        //
    }

    void StoreInst::accept(Pass &visitor) {
        visitor.visitStoreInst(this->dynamicCast<StoreInst>());
    }

    Ast StoreInst::getChildNodes() const {
        return {
            this->value,
            this->target
        };
    }

    Ptr<Value<>> StoreInst::getValue() const {
        return this->value;
    }

    void StoreInst::setValue(Ptr<Value<>> value) {
        this->value = value;
    }

    PtrRef<AllocaInst> StoreInst::getTarget() const {
        return this->target;
    }

    void StoreInst::setTarget(PtrRef<AllocaInst> target) {
        this->target = target;
    }
}
