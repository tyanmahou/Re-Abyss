#include <abyss/components/Adv/Common/Command/CharaSetter.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>

namespace abyss::Adv
{
    CharaSetter::CharaSetter(
        AdvObj* pObj,
        const s3d::Optional<CharaKind>& kind,
        const s3d::Optional<Side>& side,
        const s3d::Optional<Face>& face
    ):
        m_pObj(pObj),
        m_kind(kind),
        m_side(side),
        m_face(face)
    {}
    void CharaSetter::onStart()
    {
        auto* engine = m_pObj->engine().get();
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
