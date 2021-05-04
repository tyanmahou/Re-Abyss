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

    void Light::render(double time) const
    {
        m_view.render(time);
    }

    s3d::ScopedCustomShader2D Light::start(const s3d::ColorF& color) const
    {
        return m_view.start(color);
    }
}
