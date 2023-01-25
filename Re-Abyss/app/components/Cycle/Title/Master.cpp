#include <abyss/components/Cycle/Title/Master.hpp>

namespace abyss::Cycle::Title
{
    Master::Master(IMasterObserver* observer):
        m_observer(observer)
    {}

    bool Master::gameStart()
    {
        return this->notify(Notify::GameStart);
    }

    bool Master::exit()
    {
        return this->notify(Notify::Exit);
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

    bool Master::listen()
    {
        if (!m_observer) {
            return false;
        }
        switch (m_notify) {
        case Notify::GameStart: return m_observer->onGameStart();
        case Notify::Exit: return m_observer->onExit();
        default:
            break;
        }
        return false;
    }
}
