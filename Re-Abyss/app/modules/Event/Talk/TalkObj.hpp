#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss::Event::Talk
{
    class TalkHandler;

    class TalkObj : public GameObject
    {
    public:
        TalkObj(EventObj* pEvent);

        bool update();

        EventObj* getEvent() const
        {
            return m_pEvent;
        }
    private:
        EventObj* m_pEvent;
        Ref<TalkHandler> m_talk;
    };
}