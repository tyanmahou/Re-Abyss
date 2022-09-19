#pragma once
#include <memory>
#include <Siv3D/ColorF.hpp>
#include <Siv3D/ScopedCustomShader2D.hpp>

namespace abyss
{
    /// <summary>
    /// ブレンドモード
    /// </summary>
    enum class BlendMode
    {
        /// <summary>カラー</summary>
        Color,
    };

    /// <summary>
    /// ブレンドシェーダー
    /// </summary>
    class BlendShader
    {
        class Impl;
    public:
        BlendShader();
        ~BlendShader();

        const BlendShader& setColor(const s3d::ColorF& color) const;
        const BlendShader& setBlendMode(BlendMode mode) const;

        [[nodiscard]] s3d::ScopedCustomShader2D start() const;
    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
