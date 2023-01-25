#include <abyss/components/Cycle/DevPortal/Master.hpp>
#if ABYSS_DEVELOP
namespace abyss::Cycle::DevPortal
{
    Master::Master(IMasterObserver* observer):
        m_observer(observer)
    {}

    bool Master::notify(Notify notify)
    {
        if (!m_observer) {
            return false;
        }
        if (static_cast<s3d::int8>(m_notify) >= static_cast<s3d::int8>(notify)) {
            return false;
        }
        m_notify = notify;
        return true;
    }
    bool Master::gameStart()
    {
        if (this->notify(Notify::GameStart)) {
            m_notifyEvent = std::bind(&IMasterObserver::onGameStart, m_observer);
            return true;
        }
        return false;

    }
    bool Master::experiment()
    {
        if (this->notify(Notify::Experiment)) {
            m_notifyEvent = std::bind(&IMasterObserver::onExperiment, m_observer);
            return true;
        }
        return false;
    }
    bool Master::listen()
    {
        if (!m_observer) {
            return false;
        }
        if (!m_notifyEvent) {
            return false;
        }
        return m_notifyEvent();
    }
}
#endif
