#include <abyss/components/Adv/Common/Command/CharaSetter.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>

namespace abyss::Adv
{
    CharaSetter::CharaSetter(
        AdvObj* pObj,
        const s3d::Optional<CharaKind>& kind,
        const s3d::Optional<LookType>& look,
        const s3d::Optional<Emote>& emote
    ):
        m_pObj(pObj),
        m_kind(kind),
        m_look(look),
        m_emote(emote)
    {}
    void CharaSetter::onStart()
    {
        auto* engine = m_pObj->engine().get();
        if (m_kind) {
            engine->setCharaKind(*m_kind);
        }
        if (m_look) {
            engine->setLook(*m_look);
        }
        if (m_emote) {
            engine->setEmote(*m_emote);
        }
    }
    Coro::Fiber<> CharaSetter::onCommand()
    {
        co_return;
    }
}
