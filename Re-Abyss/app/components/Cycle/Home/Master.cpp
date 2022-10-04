#include <abyss/components/Cycle/Home/Master.hpp>

namespace abyss::Cycle::Home
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
