#include <abyss/components/UI/Home/Top/Main.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/UI/Home/Top/TopView.hpp>
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
        constexpr int32 count = static_cast<int32>(Mode::Max);
        if (InputManager::Left.down()) {
            m_mode = static_cast<Mode>((static_cast<int32>(m_mode) + count - 1) % count);
        } else if (InputManager::Right.down()) {
            m_mode = static_cast<Mode>((static_cast<int32>(m_mode) + 1) % count);
        }
    }
    void Main::onDraw() const
    {
        m_view
            ->setMode(m_mode)
            .draw();
    }
}
