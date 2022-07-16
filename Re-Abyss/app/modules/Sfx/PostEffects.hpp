#pragma once
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

        void update(double dt);

        Blur* getBlur() const;
        Scanline* getScanline() const;
    private:
        std::unique_ptr<Scanline> m_scanline;
        std::unique_ptr<Blur> m_blur;
    };
}
