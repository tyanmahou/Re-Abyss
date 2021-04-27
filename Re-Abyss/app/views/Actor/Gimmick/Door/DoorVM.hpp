#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/entities/Actor/Gimmick/DoorEntity.hpp>

namespace abyss::Actor::Gimmick::Door
{
    class DoorVM
    {
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
        DoorKind m_kind;
        double m_time = 0;

        void drawCommon() const;
        void drawBoss() const;
    public:
        DoorVM();

        DoorVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }

        DoorVM& setKind(DoorKind kind)
        {
            m_kind = kind;
            return *this;
        }
        DoorVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }

        void draw() const;
    };
}