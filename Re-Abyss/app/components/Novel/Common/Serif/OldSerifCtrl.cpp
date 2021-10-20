#include "OldSerifCtrl.hpp"

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/UI/Serif/Builder.hpp>

namespace abyss::Novel
{
    OldSerifCtrl::OldSerifCtrl(TalkObj* pTalk, const OldSerifModel& serif):
        m_pTalk(pTalk),
        m_serif(serif)
    {}
    void OldSerifCtrl::onStart()
    {
        m_pTalk->getModule<UIs>()
            ->create<UI::Serif::Builder>(m_pTalk->find<OldSerifCtrl>());
    }
    void OldSerifCtrl::onEnd()
    {}
    Coro::Task<> OldSerifCtrl::onTalk()
    {
        while (m_serif.update()) {
            co_yield{};
        }
    }
    const s3d::Optional<s3d::String>& OldSerifCtrl::getActorName() const
    {
        return m_serif.getActorName();
    }
    OldSerifModel::Side OldSerifCtrl::getSide() const
    {
        return m_serif.getSide();
    }
    const s3d::Array<OldSerifModel::Message>& OldSerifCtrl::getMessages() const
    {
        return m_serif.getMessages();
    }
    const s3d::String& OldSerifCtrl::getMessage(size_t index) const
    {
        return m_serif.getMessage(index);
    }
    s3d::int32 OldSerifCtrl::getStrIndex() const
    {
        return m_serif.getStrIndex();
    }
    bool OldSerifCtrl::isEnd() const
    {
        return m_serif.isEnd();
    }
    bool OldSerifCtrl::isAll() const
    {
        return m_serif.isAll();
    }
    bool OldSerifCtrl::isLeft() const
    {
        return m_serif.isLeft();
    }
    bool OldSerifCtrl::isRight() const
    {
        return m_serif.isRight();
    }
    s3d::String OldSerifCtrl::getPrev() const
    {
        return m_serif.getPrev();
    }
    const s3d::String& OldSerifCtrl::getCurrent() const
    {
        return m_serif.getCurrent();
    }
    const s3d::String& OldSerifCtrl::getCurrentKind() const
    {
        return m_serif.getCurrentKind();
    }
}
