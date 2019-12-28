#include <ionir/tracking/symbol_table.h>

namespace ionir {
    bool SymbolTable::insertSymbol(Symbol symbol, bool overwrite) {
        if (this->contains(symbol.name) && !overwrite) {
            return false;
        }

        return this->insert(symbol.name, symbol, overwrite);
    }
}
