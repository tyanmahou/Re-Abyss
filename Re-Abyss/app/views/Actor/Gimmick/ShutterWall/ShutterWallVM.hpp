#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/entities/Actor/Gimmick/DoorEntity.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    class ShutterWallVM
    {
    public:
        ShutterWallVM();

        ShutterWallVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        ShutterWallVM& setShutterRate(double rate)
        {
            m_shutterRate = rate;
            return *this;
        }
        ShutterWallVM& setColorMul(const s3d::ColorF color)
        {
            m_colorMul = color;
            return *this;
        }
        void draw() const;
    private:
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
        double m_shutterRate = 1.0;
        s3d::ColorF m_colorMul;
    };
}
