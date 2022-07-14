#include <abyss/components/UI/GamePause/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::GamePause
{
    void Main::Build(UIObj* pUi)
    {
        pUi->attach<Main>(pUi)
            ->setOrder(DrawOrder::UI::Pause);

    }
    Main::Main(UIObj* pUi):
        m_pUi(pUi)
    {
        m_state.reset(std::bind(&Main::stateSelect, this));
    }
    Main::~Main()
    {
    }
    void Main::onStart()
    {
    }
    void Main::onUpdate()
    {
        m_state.moveNext();
    }
    void Main::onDraw() const
    {
        s3d::Scene::Rect().draw(ColorF(0, 0.5));
    }
    Coro::Task<> Main::stateSelect()
    {
        while (true) {
            if (InputManager::Start.down()) {
                DialogResult::set({
                    .isContinue = true
                });
                co_return;
            }
            co_yield{};
        }
    }
}
