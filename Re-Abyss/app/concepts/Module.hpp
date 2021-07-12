#pragma once
#include <abyss/modules/Manager/Manager.hpp>

namespace abyss::Sys
{
    template<class Mod>
    concept Managed = requires(Mod* pMod, Manager* pManager)
    {
        pManager->set(pMod);
    };

    template<class Mod>
    concept SetManagerable = requires(Mod* pMod, Manager* pManager)
    {
        pMod->setManager(pManager);
    };
}