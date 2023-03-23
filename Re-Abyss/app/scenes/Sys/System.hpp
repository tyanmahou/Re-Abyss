#pragma once
#include <memory>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/scenes/Sys/IBooter.hpp>
#include <abyss/scenes/Sys/Modules.hpp>
#include <Emaject.hpp>

namespace abyss::Sys2
{
    class System
    {
    public:
        INJECT_CTOR(System(std::shared_ptr<IBooter> booter));

        void update();

        void draw() const;

        template<class Mod>
        inline Mod* mod() const
        {
            return m_mods->get<Mod>();
        }
    private:
        Manager m_manager;

        std::shared_ptr<Modules> m_mods;
    };
}
