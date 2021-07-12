#pragma once
#include <abyss/system/ModulePackage.hpp>
#include <abyss/system/base/IBooter.hpp>

namespace abyss::Sys
{
    template<Config config>
    class System
    {
    public:
        System():
            m_mods(&m_manager)
        {}

        bool boot(IBooter* pBooter)
        {
            return pBooter->onBoot(&m_manager);
        }
    private:
        template<class Mod>
        inline Mod* mod() const
        {
            return m_mods.get<Mod>();
        }
    private:
        Manager m_manager;

        ModulePackage<config> m_mods;
    };
}