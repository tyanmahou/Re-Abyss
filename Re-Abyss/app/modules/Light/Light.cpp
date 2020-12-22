#include "Light.hpp"
#include <abyss/debugs/DebugManager/DebugManager.hpp>

namespace abyss
{
    void Light::clear()
    {
        m_view.clear();
    }

    void Light::addLight(const LightModel& light)
    {
        LightVM vm{
            light.getPos(),
            light.getRange(),
            light.getBrightness(),
        };
        m_view.push(vm);
    }

    void Light::draw(double dt, const CameraView& camera) const
    {
#if ABYSS_DEBUG
        if (Debug::DebugManager::DisableDarkNess()) {
            return;
        }
#endif
        m_view.draw(dt, camera);
    }
}