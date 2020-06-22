#include "Master.hpp"

namespace abyss
{
    Master::Master(IMasterObserver* observer):
        m_observer(observer)
    {
    }
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
    bool Master::escape()
    {
        return this->notify(Notify::Escape);
    }
    bool Master::restart()
    {
        return this->notify(Notify::Restart);
    }

    bool Master::clear()
    {
        return this->notify(Notify::Clear);
    }

    bool Master::sendNotify()
    {
        if (!m_observer) {
            return false;
        }
        switch (m_notify) {
        case Notify::Escape: return m_observer->onEscape();
        case Notify::Restart: return m_observer->onRestart();
        case Notify::Clear: return m_observer->onClear();
        default:
            break;
        }
        return false;
    }

}
