#include <abyss/components/UI/Title/BgmCtrl.hpp>
#include <abyss/components/Sound/BgmPath.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Title
{
    BgmCtrl::BgmCtrl(UIObj* pUi):
        m_pUi(pUi)
    {}
    void BgmCtrl::onStart()
    {
        m_pUi->getModule<Sound>()
            ->play(BgmPath::Title, 0.2s);
    }
    void BgmCtrl::onEnd()
    {
        m_pUi->getModule<Sound>()
            ->stop(0.2s);
    }
}
