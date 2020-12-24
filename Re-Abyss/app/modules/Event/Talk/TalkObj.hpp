#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss::Event::Talk
{
    class TalkHandler;

    class TalkObj : public GameObject
    {
    public:
        TalkObj(IEvent* pEvent);

        bool update();

        IEvent* getEvent() const
        {
            return m_pEvent;
        }
    private:
        IEvent* m_pEvent;
        Ref<TalkHandler> m_talk;
    };
}