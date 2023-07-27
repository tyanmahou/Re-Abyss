#include <abyss/components/UI/BossArrival/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Fiber/Tween.hpp>

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
        auto* deadEffect = m_pUi->getModule<PostEffects>()->getDeadEffect();
        deadEffect->setIsValid(true);

        co_await Coro::Tween::Linear0_1(3s, m_pUi->getClock(), [&](double rate) {
            deadEffect->setColor(ColorF(1, 1 - 1 * Periodic::Triangle0_1(0.5s, rate), 0, 0.8 * Periodic::Triangle0_1(0.5s, rate)));
        });
        deadEffect->setIsValid(false);
        deadEffect->resetColor();
        m_pUi->destroy();
        co_return;
    }
}
