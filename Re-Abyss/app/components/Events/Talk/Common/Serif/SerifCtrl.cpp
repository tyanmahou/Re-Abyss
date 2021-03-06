#include "SerifCtrl.hpp"

#include <abyss/modules/Event/Talk/TalkObj.hpp>
#include <abyss/modules/UI/UI.hpp>
#include <abyss/components/UI/Serif/Builder.hpp>
#include <abyss/components/Events/Talk/Common/Serif/FaceTable.hpp>

namespace abyss::Event::Talk
{
    SerifCtrl::SerifCtrl(TalkObj* pTalk, const SerifModel& serif):
        m_pTalk(pTalk),
        m_serif(serif)
    {}
    void SerifCtrl::onStart()
    {
        m_pTalk->getModule<UI>()
            ->create<ui::Serif::Builder>(m_pTalk->find<SerifCtrl>(), m_pTalk->find<FaceTable>());
    }
    void SerifCtrl::onEnd()
    {}
    Coro::Task<> SerifCtrl::onTalk()
    {
        while (m_serif.update()) {
            co_yield{};
        }
    }
    const s3d::Optional<s3d::String>& SerifCtrl::getActorName() const
    {
        return m_serif.getActorName();
    }
    SerifModel::Side SerifCtrl::getSide() const
    {
        return m_serif.getSide();
    }
    const s3d::Array<SerifModel::Message>& SerifCtrl::getMessages() const
    {
        return m_serif.getMessages();
    }
    const s3d::String& SerifCtrl::getMessage(size_t index) const
    {
        return m_serif.getMessage(index);
    }
    s3d::int32 SerifCtrl::getStrIndex() const
    {
        return m_serif.getStrIndex();
    }
    bool SerifCtrl::isEnd() const
    {
        return m_serif.isEnd();
    }
    bool SerifCtrl::isAll() const
    {
        return m_serif.isAll();
    }
    bool SerifCtrl::isLeft() const
    {
        return m_serif.isLeft();
    }
    bool SerifCtrl::isRight() const
    {
        return m_serif.isRight();
    }
    s3d::String SerifCtrl::getPrev() const
    {
        return m_serif.getPrev();
    }
    const s3d::String& SerifCtrl::getCurrent() const
    {
        return m_serif.getCurrent();
    }
    const s3d::String& SerifCtrl::getCurrentKind() const
    {
        return m_serif.getCurrentKind();
    }
}
