#pragma once
#include <abyss/types/Actor/Gimmick/BushKind.hpp>
#include <Siv3D/Texture.hpp>

namespace abyss::Actor::Gimmick::Bush
{
    class BushVM
    {
    public:
        BushVM();

        BushVM& setKind(BushKind kind)
        {
            m_kind = kind;
            return *this;
        }
        BushVM& setPos(const s3d::Vec2& pos);
        BushVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        BushVM& setResizeRate(double rate)
        {
            m_resizeRate = rate;
            return *this;
        }
        void draw() const;
    private:
        s3d::Texture m_texture;
        BushKind m_kind;
        s3d::Vec2 m_pos;
        double m_time;
        double m_resizeRate = 0;
    };
}