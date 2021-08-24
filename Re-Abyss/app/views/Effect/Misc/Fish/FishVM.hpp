#pragma once
#include <abyss/types/Forward.hpp>

#include <Siv3D/Texture.hpp>

namespace abyss::Effect::Misc::Fish
{
    class FishVM
    {
    public:
        FishVM(s3d::int32 fishId = 0);

        FishVM& setPos(const s3d::Vec2& pos);
        FishVM& setScale(double scale)
        {
            m_scale = scale;
            return *this;
        }
        FishVM& setForward(Forward forward)
        {
            m_forward = forward;
            return *this;
        }
        FishVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        s3d::Vec2 size() const
        {
            return m_texture.size() * m_scale;
        }
        void draw(const s3d::ColorF& color = s3d::Palette::White) const;
    private:
        s3d::Texture m_texture;
        s3d::Vec2 m_pos{0, 0};
        double m_scale = 1.0;
        Forward m_forward{};
        double m_time = 0;
    };
}