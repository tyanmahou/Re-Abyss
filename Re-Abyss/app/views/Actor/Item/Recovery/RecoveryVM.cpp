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
        m_texture(U"base")(32 * baseFrame, 14, 32, 14).drawAt(m_pos + m_baseBottomOffset);

        // コア
        auto frame0_1 = Periodic::Sawtooth0_1(Param::Shared::FrameAnimTimeSec, m_time);
        frame0_1 = frame0_1 * frame0_1;
        auto frameFrame = static_cast<int32>(frame0_1 * 6.0) % 6;
        if (frameFrame >= 4) {
            frameFrame = 3;
        }
        if (m_kind == RecoveryKind::Small) {
            auto coreFrame = static_cast<int32>(Periodic::Sawtooth0_1(m_coreAnimTimeSec, m_time) * 2.0) % 2;
            m_texture(U"heal_color")(14 * coreFrame, 0, 14, 14).drawAt(m_pos + m_coreOffset);
            m_texture(U"heal_frame")(0, 14 * frameFrame, 40, 14).drawAt(m_pos + m_coreOffset);
        }
        m_texture(U"base")(32 * baseFrame, 0, 32, 14).drawAt(m_pos + m_baseTopOffset);
    }
}
