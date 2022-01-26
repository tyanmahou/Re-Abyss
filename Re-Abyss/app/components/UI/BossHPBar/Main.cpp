#include <abyss/components/UI/BossHPBar/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::BossHPBar
{
    Main::Main(UIObj* pUi):
        m_pUi(pUi)
    {}

    void Main::setup(Executer executer)
    {
        executer.on<IUpdate>().addAfter<HPGaugeCtrl>();
    }
    void Main::onStart()
    {
        m_hpGauge = m_pUi->find<HPGaugeCtrl>();
    }

    void Main::onUpdate()
    {
        if (!m_hpGauge->isValid()) {
            // 死亡したら死ぬ
            m_pUi->destroy();
            return;
        }
    }
}
