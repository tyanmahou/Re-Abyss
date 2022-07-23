#include <abyss/modules/Pause/PauseManager.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/components/Event/GamePause/Builder.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Manager/Manager.hpp>

namespace abyss::Pause
{
    PauseManager::PauseManager()
    {
    }
    void PauseManager::setPausable(bool isPausable, DisableKind kind)
    {
        if (isPausable) {
            m_pausaDisableBit &= ~(1 << static_cast<s3d::int32>(kind));
        } else {
            m_pausaDisableBit |= (1 << static_cast<s3d::int32>(kind));
        }
    }
    bool PauseManager::isPausable() const
    {
        return m_pausaDisableBit == 0;
    }
    void PauseManager::update()
    {
        if (InputManager::Start.down()) {
            if (m_obj) {
                return;
            }
            if (!this->isPausable()) {
                return;
            }
            auto pEvent = m_pManager->getModule<Events>();
            if (pEvent->isEmpty()) {
                m_obj = pEvent->create<Event::GamePause::Builder>();
            }
        }
    }
}
