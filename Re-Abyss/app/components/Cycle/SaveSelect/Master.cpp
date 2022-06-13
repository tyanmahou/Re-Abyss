#include <abyss/components/Cycle/SaveSelect/Master.hpp>

namespace abyss::Cycle::SaveSelect
{
    Master::Master(IMasterObserver* observer):
        m_observer(observer)
    {}

    bool Master::newGame(s3d::int32 userId)
    {
        return this->notify(Notify::NewGame, userId);
    }

    bool Master::loadGame(s3d::int32 userId)
    {
        return this->notify(Notify::LoadGame, userId);
    }

    bool Master::back()
    {
        return this->notify(Notify::Back, 0);

    }
    bool Master::notify(Notify notify, s3d::int32 userId)
    {
        if (!m_observer) {
            return false;
        }
        if (static_cast<s3d::int8>(m_notify) >= static_cast<s3d::int8>(notify)) {
            return false;
        }
        m_notify = notify;
        m_userId = userId;
        return true;
    }

    bool Master::listen()
    {
        if (!m_observer) {
            return false;
        }
        switch (m_notify) {
        case Notify::NewGame: return m_observer->onNewGame(m_userId);
        case Notify::LoadGame: return m_observer->onLoadGame(m_userId);
        case Notify::Back: return m_observer->onBack();
        default:
            break;
        }
        return false;
    }
}
