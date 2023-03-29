#pragma once
#include <memory>
#include <abyss/modules/FieldEnv/Bg/Bg.hpp>
#include <abyss/modules/FieldEnv/Sky/Sky.hpp>
#include <abyss/modules/FieldEnv/Caustics/Caustics.hpp>
#include <abyss/modules/FieldEnv/Fog/Fog.hpp>

namespace abyss::FieldEnv
{
    struct EnvDesc
    {
        bool useSky = false;
        bool useCaustics = false;
        bool useFog = false;
    };

    class Environment
    {
    public:
        Environment() = default;

        Environment(const EnvDesc& desc);
        void init(const EnvDesc& desc = {});

        void update(double dt);

        Bg* getBg() const
        {
            return m_bg.get();
        }
        Sky* getSky() const
        {
            return m_sky.get();
        }
        Caustics* getCaustics() const
        {
            return m_caustics.get();
        }
        Fog* getFog() const;
        void applyFog(std::function<void()> drawer, double z) const;

        void setThemeColor(const s3d::ColorF& color)
        {
            m_themeColor = color;
        }
        const s3d::Optional<s3d::ColorF>& getThemeColor() const
        {
            return m_themeColor;
        }
        s3d::ColorF getThemeColorOrDefault() const;
    private:
        std::unique_ptr<Bg> m_bg;
        std::unique_ptr<Sky> m_sky;
        std::unique_ptr<Caustics> m_caustics;
        std::unique_ptr<Fog> m_fog;

        s3d::Optional<s3d::ColorF> m_themeColor;
    };
}
