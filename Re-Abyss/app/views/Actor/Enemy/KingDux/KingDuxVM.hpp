#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/views/Actor/Enemy/KingDux/Motion.hpp>
#include <abyss/views/Shader/Dither/DitherShader.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class KingDuxVM
    {
    public:
        KingDuxVM();
        KingDuxVM& setTime(double time);
        KingDuxVM& setAnimTime(double time);
        KingDuxVM& setPos(const s3d::Vec2& pos);
        KingDuxVM& setEyePos(const s3d::Vec2& posL, const s3d::Vec2& posR);

        KingDuxVM& setIsDamaging(bool isDamaging);
        KingDuxVM& setMotion(Motion motion)
        {
            m_motion = motion;
            return *this;
        }

        KingDuxVM& setColorMul(const s3d::ColorF color);
        KingDuxVM& setColorAdd(const s3d::ColorF color);

        void draw() const;
    private:
        TexturePacker m_texture;
        s3d::Texture m_mouth;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_eyePosL{ 0, 0 };
        s3d::Vec2 m_eyePosR{ 0, 0 };
        bool m_isDamaging = false;
        double m_time = 0;
        double m_animTime = 0;
        Motion m_motion = Motion::Wait;

        s3d::ColorF m_colorMul;
        s3d::ColorF m_colorAdd;
    };
}
