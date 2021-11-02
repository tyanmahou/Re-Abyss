#include "CharaSetter.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

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
        if (m_kind) {
            m_pTalk->engine()->setCharaKind(*m_kind);
        }
        if (m_side) {
            m_pTalk->engine()->setSide(*m_side);
        }
        if (m_face) {
            m_pTalk->engine()->setFace(*m_face);
        }
    }
    Coro::Task<> CharaSetter::onCommand()
    {
        co_return;
    }
}
