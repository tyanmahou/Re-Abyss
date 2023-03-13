#pragma once
#include <abyss/components/UI/Home/Top/Mode.hpp>

namespace abyss::UI::Home::Top
{
    class ModeUpdater
    {
    public:
        ModeUpdater();

        Mode update(Mode mode) const;
    private:
        s3d::HashTable<Mode, std::array<s3d::Optional<Mode>, 4>> m_changerMap;
    };
}
