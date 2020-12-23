#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss::Event
{
    class IEvent : public GameObject
    {
    protected:
        Manager* m_pManager = nullptr;
        bool m_isWorldStop = true;
    public:
        virtual ~IEvent() = default;
        void setManager(Manager* manager)
        {
            m_pManager = manager;
        }
        virtual void onStart(){}
        virtual bool update([[maybe_unused]] double dt) { return true; }
        virtual void onEnd(){}

        void setIsWorldStop(bool isWorldStop)
        {
            m_isWorldStop = isWorldStop;
        }

        bool isWorldStop() const
        {
            return m_isWorldStop;
        }
    };
}