#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Manager/Manager.hpp>

namespace abyss::Sys::Splash
{
    class System
    {
    public:
        System();
        ~System();
        bool boot(IBooter* pBooter);

        void update();

        void draw() const;
    private:
        Manager m_manager;
    };
}