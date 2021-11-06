#pragma once
#include <abyss/modules/PostEffect/Scanline/Scanline.hpp>

namespace abyss::PostEffect
{
    /// <summary>
    /// ポストエフェクト
    /// </summary>
    class PostEffects
    {
    public:
        PostEffects();

        void update(double dt);

        Scanline* getScanline() const;
    private:
        std::unique_ptr<Scanline> m_scanline;
    };
}