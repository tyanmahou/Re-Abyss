#include <abyss/views/Actor/Enemy/KingDux/KingDuxVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    KingDuxVM::KingDuxVM() :
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/KingDux/KingDux.json")),
        m_mouth(Resource::Assets::Main()->load(U"Actor/Enemy/KingDux/Mouth.png"))
    {}
    KingDuxVM& KingDuxVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    KingDuxVM& KingDuxVM::setAnimTime(double time)
    {
        m_animTime = time;
        return *this;
    }
    KingDuxVM& KingDuxVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    KingDuxVM& KingDuxVM::setEyePos(const s3d::Vec2& posL, const s3d::Vec2& posR)
    {
        m_eyePosL = posL;
        m_eyePosR = posR;
        return *this;
    }
    KingDuxVM& KingDuxVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    KingDuxVM& KingDuxVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }
    KingDuxVM& KingDuxVM::setColorAdd(const s3d::ColorF color)
    {
        m_colorAdd = color;
        return *this;
    }
    void KingDuxVM::draw() const
    {
        auto color = m_colorMul;
        s3d::ScopedColorAdd2D addColor(m_colorAdd);

        auto deadAlpha = 1.0;
        if (m_motion == Motion::Dead) {
            deadAlpha = s3d::Saturate(1.0 - m_animTime);
            color.a *= deadAlpha;
        }
        if (m_motion != Motion::Hide) {
            auto eyeDraw = [&](const Vec2& eyePos, const Vec2& offset, float damageRadius) {
                auto posBase = m_pos + offset;
                Circle(posBase, 80).draw(ColorF(1, deadAlpha));
                double r = 24;
                if (m_isDamaging || m_motion == Motion::Dead) {
                    double rate = s3d::Periodic::Triangle0_1(0.3, m_time);
                    r = s3d::Math::Lerp(r, damageRadius, rate);
                    Shape2D::Cross(r, 15, posBase + eyePos).draw(ColorF(0, deadAlpha));
                    return;
                }
                Circle(posBase + eyePos, r).draw(ColorF(0, deadAlpha));
            };
            // 右目
            eyeDraw(m_eyePosR, Param::Base::EyeR, 18.0);
            // 左目
            eyeDraw(m_eyePosL, Param::Base::EyeL, 36.0);
        }

        // 体
        {
            auto rate = s3d::Periodic::Sine0_1(5.0, m_time);
            auto offsetX = s3d::Math::Lerp(-0.01, 0.01, rate);
            auto tex = m_motion != Motion::Hide ? m_texture(U"base") : m_texture(U"crown");
            tex.scaled(1.0 + offsetX, 1.0).drawAt(m_pos, color);
        }
        // 口
        if (m_motion != Motion::Hide) {
            auto rate = s3d::Periodic::Sine0_1(4.0, m_time);
            auto offsetX = 0.15 * (1 - rate);
            auto offsetY = s3d::Math::Lerp(-0.3, 0.2, rate) / 2.0;

            if (m_motion == Motion::Wait || m_motion == Motion::Dead) {
                m_mouth(0, 0, 300, 240).scaled(1.0 + offsetX, 1.0 + offsetY).drawAt(m_pos + Param::Base::MouthPos, color);
            } else if(m_motion == Motion::Angry) {
                auto page = static_cast<int32>(Periodic::Sawtooth0_1(1.0s, m_animTime) * 6);
                if (m_animTime >= 1) {
                    page = 5;
                } else if (m_animTime <= 0) {
                    page = 0;
                }
                const Vec2 mouthOffs{ 0, -20 * m_animTime };
                m_mouth((page % 2) * 300, (page / 2) * 240, 300, 240).scaled(1.0 + offsetX, 1.0 + offsetY).drawAt(m_pos + Param::Base::MouthPos + mouthOffs, color);
            }
        }
    }
}
