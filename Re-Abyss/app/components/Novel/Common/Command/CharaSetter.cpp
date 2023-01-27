#include <abyss/components/Novel/Common/Command/CharaSetter.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Novel/base/Engine.hpp>

namespace abyss::Novel
{
    CharaSetter::CharaSetter(
        TalkObj* pTalk,
        const s3d::Optional<CharaKind>& kind,
        const s3d::Optional<Side>& side,
        const s3d::Optional<Face>& face
    ):
        m_pTalk(pTalk),
        m_kind(kind),
        m_side(side),
        m_face(face)
    {}
    void CharaSetter::onStart()
    {
        auto* engine = m_pTalk->engine().get();
        if (m_kind) {
            engine->setCharaKind(*m_kind);
        }
        if (m_side) {
            engine->setSide(*m_side);
        }
        if (m_face) {
            engine->setFace(*m_face);
        }
    }
    Coro::Fiber<> CharaSetter::onCommand()
    {
        co_return;
    }
}
