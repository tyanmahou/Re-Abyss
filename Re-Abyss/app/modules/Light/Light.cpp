#include "Light.hpp"
#include <abyss/debugs/Menu/Menu.hpp>

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

    void Light::draw(double time, const CameraView& camera) const
    {
#if ABYSS_DEBUG
        if (Debug::Menu::IsDebug(U"disable-darkness")) {
            return;
        }
#endif
        m_view.draw(time, camera);
    }
}
