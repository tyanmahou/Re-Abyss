#include "Builder.hpp"
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/components/Decor/General/SchoolOfFish/Drawer.hpp>

namespace abyss::Decor::General::SchoolOfFish
{
    void Builder::Build(DecorObj* pObj)
    {
        pObj->attach<Drawer>(pObj);
    }
}