#include <abyss/components/Adv/Common/Command/Bgm.hpp>

#include <abyss/commons/Path.hpp>
#include <abyss/modules/Sound/Sounds.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv
{
    Bgm::Bgm(
        AdvObj* pObj,
        Kind kind,
        const s3d::String& path,
        const Duration& fade
    ):
        m_pObj(pObj),
        m_kind(kind),
        m_path(path),
        m_fade(fade)
    {}
    void Bgm::onStart()
    {
        auto* pSound = m_pObj->getModule<Sounds>();
        switch (m_kind)
        {
        case Kind::Play:
            pSound->play(Path::SoundPath + m_path, m_fade);
            break;
        case Kind::Stop:
            pSound->stop(m_fade);
            break;
        case Kind::Stash:
            pSound->stash(m_fade);
            break;
        case Kind::StashPop:
            pSound->stashPop(m_fade);
            break;
        default:
            break;
        }
    }
    Coro::Fiber<> Bgm::onCommand()
    {
        co_return;
    }
}
