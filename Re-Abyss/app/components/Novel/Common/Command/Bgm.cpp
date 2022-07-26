#include <abyss/components/Novel/Common/Command/Bgm.hpp>

#include <abyss/commons/Path.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel
{
    Bgm::Bgm(
        TalkObj* pTalk,
        Kind kind,
        const s3d::String& path,
        const Duration& fade
    ):
        m_pTalk(pTalk),
        m_kind(kind),
        m_path(path),
        m_fade(fade)
    {}
    void Bgm::onStart()
    {
        auto* pSound = m_pTalk->getModule<Sound>();
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
    Coro::Task<> Bgm::onCommand()
    {
        co_return;
    }
}