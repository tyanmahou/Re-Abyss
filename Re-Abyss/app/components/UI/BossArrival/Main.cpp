#include <abyss/components/UI/BossArrival/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include "Main.hpp"

namespace abyss::UI::BossArrival
{
    Main::Main(UIObj* pUi) :
        m_pUi(pUi)
    {}

    void Main::setup(Executer executer)
    {
    }
    void Main::onStart()
    {
        m_fiber.reset(std::bind(&Main::updateAsync, this));
    }

    void Main::onUpdate()
    {
        m_fiber.resume();
    }
    Coro::Fiber<void> Main::updateAsync()
    {
        co_return;
    }
}
