#include <abyss/components/UI/Home/Top/Main.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/UI/Home/Top/TopView.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Home/Top/ModeUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Home::Top
{
    Main::Main(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<TopView>())
    {
        ModeUtil::ForEach([&](Mode mode) {
            m_modeLocked[mode] = ModeUtil::IsLocked(pUi, mode);
            m_view->setLock(mode, m_modeLocked[mode]);
        });
    }
    Main::~Main()
    {
    }
    void Main::onUpdate()
    {
        m_time += m_pUi->deltaTime();

        // Modeの変更
        {
            auto modePrev = m_mode;
            m_mode = m_modeUpdater.update(m_mode);

            if (m_mode != modePrev) {
                m_time = 0;
            }
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
