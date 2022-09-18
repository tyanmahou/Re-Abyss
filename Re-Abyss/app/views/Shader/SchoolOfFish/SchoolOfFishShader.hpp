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
        ~SchoolOfFishShader();

        const SchoolOfFishShader& setPos(const s3d::Vec2& pos) const;
        const SchoolOfFishShader& setSpeed(double speed) const;
        const SchoolOfFishShader& setAngle(double angle) const;
        const SchoolOfFishShader& setHeightOffset(double heightOffset) const;
        const SchoolOfFishShader& setAmplitude(double amplitude) const;
        const SchoolOfFishShader& setTime(double time) const;
        const SchoolOfFishShader& setSize(s3d::int32 column, s3d::int32 row) const;
        const SchoolOfFishShader& setScale(double scale) const;
        const SchoolOfFishShader& setTexture(const s3d::Texture& texture) const;

        s3d::ScopedCustomShader2D start() const;

    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
