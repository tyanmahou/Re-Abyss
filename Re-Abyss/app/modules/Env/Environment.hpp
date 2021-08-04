#pragma once
#include <memory>
#include <abyss/modules/Env/Bg/Bg.hpp>
#include <abyss/modules/Env/Sky/Sky.hpp>
#include <abyss/modules/Env/WaterSurface/WaterSurface.hpp>

namespace abyss::Env
{
    class Bg;
    class Sky;
    class WaterSurface;

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
        Sky* geSky() const
        {
            return m_sky.get();
        }
        WaterSurface* getWaterSurface() const
        {
            return m_waterSurface.get();
        }
    private:
        std::unique_ptr<Bg> m_bg;
        std::unique_ptr<Sky> m_sky;
        std::unique_ptr<WaterSurface> m_waterSurface;
    };
}