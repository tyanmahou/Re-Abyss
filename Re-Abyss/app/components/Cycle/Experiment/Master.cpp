#include <abyss/components/Cycle/Experiment/Master.hpp>
#if ABYSS_DEVELOP
namespace abyss::Cycle::Experiment
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
    bool Master::exit()
    {
        if (this->notify(Notify::Exit)) {
            m_notifyEvent = std::bind(&IMasterObserver::onExit, m_observer);
            return true;
        }
        return false;
    }
    bool Master::onChangeTopic(size_t index)
    {
        if (this->notify(Notify::ChangeTopic)) {
            m_notifyEvent = std::bind(&IMasterObserver::onChangeTopic, m_observer, index);
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
        bool result = m_notifyEvent();
        m_notifyEvent = nullptr;
        return result;
    }
}
#endif
