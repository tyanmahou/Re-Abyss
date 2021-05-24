#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Texture.hpp>
#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>

namespace abyss::Actor::Item::Recovery
{
    class RecoveryVM
    {
        s3d::Texture m_texture;
        s3d::Vec2 m_pos;
        RecoveryKind m_kind;
        double m_time = 0;

    public:
        RecoveryVM();

        RecoveryVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        RecoveryVM& setKind(RecoveryKind kind)
        {
            m_kind = kind;
            return *this;
        }
        RecoveryVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }

        void draw() const;
    };
}