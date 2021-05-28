#include "RecoveryVM.hpp"

#include <abyss/commons/Resource/Assets/Assets.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Item::Recovery
{
    RecoveryVM::RecoveryVM():
        RecoveryVM(Setting{})
    {}

    RecoveryVM::RecoveryVM(const Setting & setting):
        m_texture(Resource::Assets::Main()->loadTexturePacker(U"actors/Item/Recovery/recovery.json")),
        m_coreOffset(setting.coreOffset),
        m_coreAnimTimeSec(setting.coreAnimTimeSec),
        m_baseTopOffset(setting.baseTopOffset),
        m_baseBottomOffset(setting.baseBottomOffset)
    {}

    RecoveryVM& RecoveryVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }

    void RecoveryVM::draw() const
    {
        auto baseFrame = static_cast<int32>(Periodic::Sawtooth0_1(Param::Shared::BaseAnimTimeSec, m_time) * 6.0) % 6;
        m_texture(U"base")(31 * baseFrame, 13, 31, 13).draw(m_pos + m_baseBottomOffset - Vec2{15, 6});

        // コア
        auto frameFrame = static_cast<int32>(Periodic::Sawtooth0_1(Param::Shared::FrameAnimTimeSec, m_time) * 4.0) % 4;
        if (m_kind == RecoveryKind::Small) {
            auto coreFrame = static_cast<int32>(Periodic::Sawtooth0_1(m_coreAnimTimeSec, m_time) * 2.0) % 2;
            m_texture(U"heal_color")(13 * coreFrame, 0, 13, 13).draw(m_pos + m_coreOffset - Vec2{ 6, 6 });
            m_texture(U"heal_frame")(0, 13 * frameFrame, 31, 13).draw(m_pos + m_coreOffset - Vec2{ 15, 6 });
        }
        m_texture(U"base")(31 * baseFrame, 0, 31, 13).draw(m_pos + m_baseTopOffset - Vec2{ 15, 6 });
    }
}
