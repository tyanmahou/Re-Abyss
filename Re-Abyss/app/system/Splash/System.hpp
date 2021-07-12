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
        std::unique_ptr<GlobalTime> m_time;
        std::unique_ptr<UIs> m_userInterface;
        std::unique_ptr<DrawManager> m_drawer;
        std::unique_ptr<CycleMaster> m_cycleMaster;
        Manager m_manager;
    };
}