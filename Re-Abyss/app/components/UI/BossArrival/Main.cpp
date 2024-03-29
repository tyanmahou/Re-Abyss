#include <abyss/components/UI/BossArrival/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Fiber/Tween.hpp>

#include <abyss/views/UI/BossArrival/BossArrivalVM.hpp>

namespace abyss::UI::BossArrival
{
    Main::Main(UIObj* pUi) :
        m_pUi(pUi),
        m_timer(3.0),
        m_view(std::make_unique<BossArrivalVM>())
    {}
    Main::~Main()
    {}
    void Main::setup([[maybe_unused]]Executer executer)
    {
    }
    void Main::onStart()
    {
        m_fiber.reset(std::bind(&Main::updateAsync, this));
    }

    void Main::onUpdate()
    {
        m_fiber.resume();
        m_timer.update(m_pUi->deltaTime());
    }
    Coro::Fiber<void> Main::updateAsync()
    {
        auto* deadEffect = m_pUi->getModule<PostEffects>()->getDeadEffect();
        deadEffect->setIsValid(true);
        co_await Coro::Tween::Linear(3s, [&](double rate) {
            auto c = Periodic::Triangle0_1(0.5s, rate);
            deadEffect->setColor(ColorF(1, 1 - 1 * c, 0, 0.8 * c));
        }, m_pUi->getClock());
        deadEffect->setIsValid(false);
        deadEffect->resetColor();
        m_pUi->destroy();
        co_return;
    }
    void Main::onDraw() const
    {
        m_view
            ->setTimeRate(m_timer.rate())
            .draw();
    }
}
