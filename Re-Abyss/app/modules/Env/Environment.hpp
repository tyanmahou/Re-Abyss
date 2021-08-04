#pragma once
#include <memory>
#include <abyss/modules/Env/Bg/Bg.hpp>
#include <abyss/modules/Env/Sky/Sky.hpp>
#include <abyss/modules/Env/WaterSurface/WaterSurface.hpp>
#include <abyss/modules/Env/Wave/Wave.hpp>

namespace abyss::Env
{
    struct EnvDesc
    {
        bool useSky = false;
        bool useWaterSurface = false;
        bool useWave = false;
    };

    class Environment
    {
    public:
        Environment() = default;

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
        WaterSurface* getWaterSurface() const
        {
            return m_waterSurface.get();
        }

        void applyWave(std::function<void()> drawer) const;
    private:
        std::unique_ptr<Bg> m_bg;
        std::unique_ptr<Sky> m_sky;
        std::unique_ptr<WaterSurface> m_waterSurface;
        std::unique_ptr<Wave> m_wave;
    };
}