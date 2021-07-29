#pragma once
#include <abyss/system/ModulePackage.hpp>

namespace abyss::Sys
{
    template<Config config>
    class System
    {
    public:
        System():
            m_mods(&m_manager)
        {}

        /// <summary>
        /// 起動
        /// </summary>
        /// <param name="pBooter"></param>
        /// <returns></returns>
        bool boot(IBooter* pBooter);

        void update();

        void draw() const;

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