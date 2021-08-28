#include "RecoveryVM.hpp"

#include <abyss/commons/Resource/Assets/Assets.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Item::Recovery
{
    RecoveryVM::RecoveryVM():
        RecoveryVM(Setting{})
    {}

    RecoveryVM::RecoveryVM(const Setting & setting):
        m_texture(Resource::Assets::Main()->load(U"actors/Item/Recovery/recovery.json")),
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
        const auto color = ColorF(1.0, m_alpha);

        auto offset = Vec2{ 0, Sin(m_time * 2.0) * 1.0 };
        auto baseFrame = static_cast<int32>(Periodic::Sawtooth0_1(Param::Shared::BaseAnimTimeSec, m_time) * 6.0) % 6;
        m_texture(U"base")(32 * baseFrame, 14, 32, 14).drawAt(m_pos + m_baseBottomOffset + offset, color);

        // コア
        auto frame0_1 = Periodic::Sawtooth0_1(Param::Shared::FrameAnimTimeSec, m_time);
        frame0_1 = frame0_1 * frame0_1;
        auto frameFrame = static_cast<int32>(frame0_1 * 6.0) % 6;
        if (frameFrame >= 4) {
            frameFrame = 3;
        }
        if (m_kind == RecoveryKind::Small) {
            auto coreFrame = static_cast<int32>(Periodic::Sawtooth0_1(m_coreAnimTimeSec, m_time) * 2.0) % 2;
            m_texture(U"heal_color")(14 * coreFrame, 0, 14, 14).drawAt(m_pos + m_coreOffset, color);

            if (frameFrame > 0) {
                auto frameLeft =
                    frameFrame == 1 ? 6 :
                    frameFrame == 2 ? 3 :
                    0;
                auto frameTex = m_texture(U"heal_frame")(frameLeft, 0, 20 - frameLeft, 14);

                frameTex.draw(m_pos + m_coreOffset - Vec2{ 20 - frameLeft , 7 }, color);
                frameTex.mirrored().draw(m_pos + m_coreOffset - Vec2{ 0, 7 }, color);
            }
        } else if (m_kind == RecoveryKind::Middle) {
            auto coreFrame = static_cast<int32>(Periodic::Sawtooth0_1(m_coreAnimTimeSec, m_time) * 2.0) % 2;
            m_texture(U"heal_middle_color")(20 * coreFrame, 0, 20, 20).drawAt(m_pos + m_coreOffset, color);

            if (frameFrame > 0) {
                auto frameLeft =
                    frameFrame == 1 ? 7 :
                    frameFrame == 2 ? 3 :
                    0;
                auto frameTex = m_texture(U"heal_middle_frame")(frameLeft, 0, 22 - frameLeft, 14);

                frameTex.draw(m_pos + m_coreOffset - Vec2{ 22 - frameLeft , 7 }, color);
                frameTex.mirrored().draw(m_pos + m_coreOffset - Vec2{ 0, 7 }, color);
            }
        } else if (m_kind == RecoveryKind::Big) {
            auto coreFrame = static_cast<int32>(Periodic::Sawtooth0_1(m_coreAnimTimeSec, m_time) * 2.0) % 2;
            m_texture(U"heal_big_color")(24 * coreFrame, 0, 24, 24).drawAt(m_pos + m_coreOffset, color);

            if (frameFrame > 0) {
                auto frameLeft =
                    frameFrame == 1 ? 12 :
                    frameFrame == 2 ? 7 :
                    0;
                auto frameTex = m_texture(U"heal_big_frame")(frameLeft, 0, 30 - frameLeft, 20);

                frameTex.draw(m_pos + m_coreOffset - Vec2{ 30 - frameLeft , 10 }, color);
                frameTex.mirrored().draw(m_pos + m_coreOffset - Vec2{ 0, 10 }, color);
            }
        }
        m_texture(U"base")(32 * baseFrame, 0, 32, 14).drawAt(m_pos + m_baseTopOffset - offset, color);
    }
}
