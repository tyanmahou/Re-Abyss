#include <abyss/components/UI/Home/Top/Main.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/UI/Home/Top/TopView.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Home::Top
{
    Main::Main(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<TopView>())
    {}
    Main::~Main()
    {
    }
    void Main::onUpdate()
    {
        m_time += m_pUi->deltaTime();
        constexpr int32 count = static_cast<int32>(Mode::Max);
        auto modePrev = m_mode;
        if (InputManager::Left.down()) {
            m_mode = static_cast<Mode>((static_cast<int32>(m_mode) + count - 1) % count);
        } else if (InputManager::Right.down()) {
            m_mode = static_cast<Mode>((static_cast<int32>(m_mode) + 1) % count);
        }
        if (m_mode != modePrev) {
            m_time = 0;
        }
    }
    void Main::onDraw() const
    {
        m_view
            ->setTime(m_time)
            .setMode(m_mode)
            .draw();
    }
}
