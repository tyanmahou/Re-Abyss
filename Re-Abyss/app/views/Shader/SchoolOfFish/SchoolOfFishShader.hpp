#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/ScopedCustomShader2D.hpp>

namespace abyss
{
    /// <summary>
    /// 魚の群れ
    /// </summary>
    class SchoolOfFishShader
    {
        class Impl;
    public:
        SchoolOfFishShader();

        const SchoolOfFishShader& setTime(double time) const;
        const SchoolOfFishShader& setTexture(const s3d::Texture& texture) const;

        s3d::ScopedCustomShader2D start() const;

    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}