#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Sfx/Moisture/Moisture.hpp>
#include <abyss/modules/Sfx/Bloom/Bloom.hpp>
#include <abyss/modules/Sfx/Blur/Blur.hpp>
#include <abyss/modules/Sfx/Scanline/Scanline.hpp>

namespace abyss::Sfx
{
    /// <summary>
    /// ポストエフェクト
    /// </summary>
    class PostEffects
    {
    public:
        PostEffects();

        void setManager(Manager* pManager);
        void update(double dt);

        Bloom* getBloom() const;
        Moisture* getMoisture() const;
        Blur* getBlur() const;
        Scanline* getScanline() const;
    private:
        Manager* m_pManager;
        std::unique_ptr<Bloom> m_bloom;
        std::unique_ptr<Moisture> m_moisture;
        std::unique_ptr<Blur> m_blur;
        std::unique_ptr<Scanline> m_scanline;
    };
}
