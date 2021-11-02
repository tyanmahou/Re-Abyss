#include "CharaSetter.hpp"

namespace abyss::Novel
{
    CharaSetter::CharaSetter(TalkObj* pTalk, CharaKind kind, Side side, const Face& face):
        m_pTalk(pTalk),
        m_kind(kind),
        m_side(side),
        m_face(face)
    {}
    void CharaSetter::onStart()
    {
    }
    Coro::Task<> CharaSetter::onCommand()
    {
        co_return;
    }
}
