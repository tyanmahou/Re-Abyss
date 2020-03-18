#include "Light.hpp"

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

    void Light::draw(const CameraView& camera) const
    {
        m_view.draw(camera);
    }
}
