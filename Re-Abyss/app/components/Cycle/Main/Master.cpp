#include <abyss/components/Cycle/Main/Master.hpp>

namespace abyss::Cycle::Main
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

    bool Master::escape()
    {
        if (this->notify(Notify::Escape)) {
            m_notifyEvent = std::bind(&IMasterObserver::onEscape, m_observer);
            return true;
        }
        return false;
    }

    bool Master::restart()
    {
        if (this->notify(Notify::Restart)) {
            m_notifyEvent = std::bind(&IMasterObserver::onRestart, m_observer);
            return true;
        }
        return false;
    }

    bool Master::clear()
    {
        if (this->notify(Notify::Clear)) {
            m_notifyEvent = std::bind(&IMasterObserver::onClear, m_observer);
            return true;
        }
        return false;
    }

    bool Master::moveStage(const s3d::String& link, s3d::int32 startId)
    {
        if (this->notify(Notify::MoveStage)) {
            m_notifyEvent = std::bind(&IMasterObserver::onMoveStage, m_observer, link, startId);
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
