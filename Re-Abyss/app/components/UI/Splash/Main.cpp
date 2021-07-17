#include "Main.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/components/Cycle/Splash/Master.hpp>

namespace abyss::UI::Splash
{
    Main::Main(UIObj* pUi):
        m_pUi(pUi)
    {}

    void Main::setup(Executer executer)
    {
        executer.on<IUpdate>().addAfter<Logo::LogoCtrl>();
    }
    void Main::onStart()
    {
        m_logo = m_pUi->find<Logo::LogoCtrl>();
    }

    void Main::onUpdate()
    {
        if (m_logo->isEnd()) {
            m_pUi->getModule<CycleMaster>()->find<Cycle::Splash::Master>()->chageOpDemoScene();
        }
    }
}
