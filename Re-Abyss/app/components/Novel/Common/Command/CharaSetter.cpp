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
        auto* engine = m_pTalk->engine().get();
        const auto& curtSerif = engine->getSerif();

        // キャラか位置が変わったらバッファクリア
        const bool isChangeChara = m_kind && *m_kind != curtSerif.getKind();
        const bool isChangeSide = m_side && *m_side != curtSerif.getSide();
        bool isClearBuffer = isChangeChara || isChangeSide;

        if (m_kind) {
            engine->setCharaKind(*m_kind);
        }
        if (m_side) {
            engine->setSide(*m_side);
        } else if (isChangeChara) {
            engine->setSide(Side::Left);
        }
        if (m_face) {
            engine->setFace(*m_face);
        } else if (isChangeChara) {
            engine->setFace(Face{});
        }
        if (isClearBuffer) {
            engine->clearBuffer();
        }
    }
    Coro::Task<> CharaSetter::onCommand()
    {
        co_return;
    }
}
