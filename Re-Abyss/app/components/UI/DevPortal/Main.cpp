#if ABYSS_DEVELOP
#include <abyss/components/UI/DevPortal/Main.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/components/Cycle/DevPortal/Master.hpp>
#include <abyss/commons/FontName.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>

namespace abyss::UI::DevPortal
{
    Main::Main(UIObj* pUi):
        m_pUi(pUi)
    {
    }

    void Main::onUpdate()
    {
        if (InputManager::Left.down()) {
            m_mode = Mode::GameStart;
        } else if (InputManager::Right.down()) {
            m_mode = Mode::Experiment;
        }

        if (InputManager::A.down() || InputManager::Start.down()) {

            if (m_mode == Mode::GameStart) {
                m_pUi->getModule<CycleMaster>()->find<Cycle::DevPortal::Master>()->gameStart();
            } else if (m_mode == Mode::Experiment) {
                m_pUi->getModule<CycleMaster>()->find<Cycle::DevPortal::Master>()->experiment();
            }
        }
    }

    void Main::onDraw() const
    {
        if (m_mode == Mode::GameStart) {
            FontAsset(FontName::Tips)(U"← GameStart →").draw();
        } else if (m_mode == Mode::Experiment) {
            FontAsset(FontName::Tips)(U"← Experiment →").draw();
        }
    }
}
#endif
