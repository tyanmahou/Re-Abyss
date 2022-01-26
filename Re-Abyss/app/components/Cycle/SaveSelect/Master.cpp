#include <abyss/components/Cycle/SaveSelect/Master.hpp>

namespace abyss::Cycle::SaveSelect
{
    Master::Master(IMasterObserver* observer):
        m_observer(observer)
    {}

    bool Master::newGame()
    {
        return this->notify(Notify::NewGame);
    }

    bool Master::loadGame()
    {
        return this->notify(Notify::LoadGame);
    }

    bool Master::back()
    {
        return this->notify(Notify::Back);

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
        case Notify::NewGame: return m_observer->onNewGame();
        case Notify::LoadGame: return m_observer->onLoadGame();
        case Notify::Back: return m_observer->onBack();
        default:
            break;
        }
        return false;
    }
}