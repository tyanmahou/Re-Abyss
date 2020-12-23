#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss::Event
{
    class StreamHandler;

    class IEvent : public GameObject
    {
    private:
        Ref<StreamHandler> m_stream;
    protected:
        Manager* m_pManager = nullptr;
        bool m_isWorldStop = true;
    public:
        IEvent();

        virtual ~IEvent() = default;
        void setManager2(Manager* manager)
        {
            m_pManager = manager;
        }
        virtual void onStart(){}
        bool update();
        virtual bool update([[maybe_unused]] double dt) { return false; }
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