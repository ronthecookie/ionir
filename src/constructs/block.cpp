#include "block.h"
#include "passes/pass.h"

namespace ionir
{
Block::Block(std::vector<Ptr<Section>> sections)
    : Construct(ConstructKind::Block), sections(sections), cachedEntry(std::nullopt)
{
    //
}

Ptr<Construct> Block::accept(Pass *visitor)
{
    return visitor->visitBlock(this->cast<Block>());
}

bool Block::verify() const
{
    bool entryFound = false;

    /**
     * Loop through all sections to determine
     * whether multiple entry sections exist.
     */
    for (const auto section : this->sections)
    {
        if (section->getKind() == SectionKind::Entry)
        {
            // Multiple entry sections exist.
            if (entryFound)
            {
                return false;
            }

            // Raise the flag.
            entryFound = true;
        }
    }

    return true;
}

std::optional<Ptr<Section>> Block::getEntrySection()
{
    /**
     * Entry section has already been previously
     * found, return the cached value.
     */
    if (this->cachedEntry.has_value())
    {
        return *this->cachedEntry;
    }

    for (auto section : this->sections)
    {
        if (section->getKind() == SectionKind::Entry)
        {
            // Save the result for faster subsequent access.
            this->cachedEntry = section;

            return this->cachedEntry;
        }
    }

    // Entry section was neither cached nor found.
    return std::nullopt;
}

std::vector<Ptr<Section>> Block::getSections() const
{
    return this->sections;
}

void Block::setSections(std::vector<Ptr<Section>> sections)
{
    this->sections = sections;
}
} // namespace ionir