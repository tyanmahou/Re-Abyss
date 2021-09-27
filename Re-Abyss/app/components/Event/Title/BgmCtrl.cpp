#include "BgmCtrl.hpp"
#include <abyss/commons/Path.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <Siv3D.hpp>

namespace abyss::Event::Title
{
    BgmCtrl::BgmCtrl(EventObj* pEvent):
        m_pEvent(pEvent)
    {}
    void BgmCtrl::onStart()
    {
        m_pEvent->getModule<Sound>()
            ->play(Path::SoundPath + U"bgm/cycle/title/title.aas", 0.2s);
    }
    void BgmCtrl::onEnd()
    {
        m_pEvent->getModule<Sound>()
            ->stop(0.2s);
    }
}
