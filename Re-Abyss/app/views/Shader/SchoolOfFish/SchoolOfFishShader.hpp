#pragma once
#include <memory>
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

        const SchoolOfFishShader& setPos(const s3d::Vec2& pos) const;
        const SchoolOfFishShader& setVelocity(const s3d::Vec2& velocity) const;
        const SchoolOfFishShader& setTime(double time) const;
        const SchoolOfFishShader& setSize(s3d::int32 column, s3d::int32 row) const;
        const SchoolOfFishShader& setTexture(const s3d::Texture& texture) const;

        s3d::ScopedCustomShader2D start() const;

    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}