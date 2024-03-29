#if ABYSS_DEVELOP
#include <abyss/components/UI/Experiment/Main.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/components/Cycle/Experiment/Master.hpp>
#include <abyss/components/UI/Experiment/ITopic.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>

namespace abyss::UI::Experiment
{
    Main::Main(UIObj* pUi) :
        m_pUi(pUi)
    {
    }

    void Main::onUpdate()
    {
        if (m_topic) {
            m_topic->update();
        }
        if (InputManager::Start.down()) {
            m_pUi->getModule<CycleMaster>()->find<Cycle::Experiment::Master>()->exit();
        }
    }

    void Main::onDraw() const
    {
        if (m_topic) {
            m_topic->draw();
        }
    }
}
#endif
