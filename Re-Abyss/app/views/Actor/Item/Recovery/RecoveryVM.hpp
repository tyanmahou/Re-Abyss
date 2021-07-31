#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>
#include <abyss/params/Actor/Item/Recovery/Param.hpp>

namespace abyss::Actor::Item::Recovery
{
    class RecoveryVM
    {
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_coreOffset;
        double m_coreAnimTimeSec;
        s3d::Vec2 m_baseTopOffset;
        s3d::Vec2 m_baseBottomOffset;
        RecoveryKind m_kind;
        double m_time = 0;

        double m_alpha = 1.0;
    public:
        RecoveryVM();
        RecoveryVM(const Setting& setting);

        RecoveryVM& setPos(const s3d::Vec2& pos);
        RecoveryVM& setCoreOffset(const s3d::Vec2& pos)
        {
            m_coreOffset = pos;
            return *this;
        }

        RecoveryVM& setCoreAnimTimeSec(double time)
        {
            m_coreAnimTimeSec = time;
            return *this;
        }
        RecoveryVM& setBaseOffset(const s3d::Vec2& top, const s3d::Vec2& bottom)
        {
            m_baseTopOffset = top;
            m_baseBottomOffset = bottom;
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
        RecoveryVM& setAlpha(double alpha)
        {
            m_alpha = alpha;
            return *this;
        }
        void draw() const;
    };
}