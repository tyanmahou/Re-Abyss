#include "Master.hpp"

namespace abyss::Cycle::Splash
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

    bool Master::chageOpDemoScene()
    {
        return this->notify(Notify::ChageOpDemoScene);
    }

    bool Master::listen()
    {
        if (!m_observer) {
            return false;
        }
        switch (m_notify) {
        case Notify::ChageOpDemoScene: return m_observer->chageOpDemoScene();
        default:
            break;
        }
        return false;
    }
}