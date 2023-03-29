#include <abyss/modules/FieldEnv/Environment.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/debugs/Debug.hpp>

namespace abyss::FieldEnv
{
    Environment::Environment(const EnvDesc& desc)
    {
        this->init(desc);
    }
    void Environment::init(const EnvDesc& desc)
    {
        m_bg = std::make_unique<Bg>();
        if (desc.useSky) {
            m_sky = std::make_unique<Sky>();
        }
        if (desc.useCaustics) {
            m_caustics = std::make_unique<Caustics>();
        }
        if (desc.useFog) {
            m_fog = std::make_unique<Fog>();
        }
    }
    void Environment::update(double dt)
    {
        if (m_sky) {
            m_sky->update(dt);
        }
        if (m_caustics) {
            m_caustics->update(dt);
        }
    }
    Fog* Environment::getFog() const
    {
#if ABYSS_DEBUG
        if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::RenderFog)) {
            return nullptr;
        }
#endif
        return m_fog.get();
    }
    void Environment::applyFog(std::function<void()> drawer, double z) const
    {
        if (z > 0.0) {
            if (auto fog = this->getFog()) {
                auto fogShader = fog->setZ(z).start();
                drawer();
            } else {
                drawer();
            }
        } else {
            drawer();
        }
    }
    s3d::ColorF Environment::getThemeColorOrDefault() const
    {
        return m_themeColor.value_or(ColorDef::DefaultFadeColor);
    }
}
