#include "KiraKiraEffect.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>
namespace abyss
{
    KiraKiraEffect::KiraKiraEffect(const s3d::Vec2& pos, Type type) :
        m_type(type),
        m_pos(pos),
        m_texture(Resource::Assets::Main()->load(U"actors/Common/common_effects.json"))
    {}

    bool KiraKiraEffect::update(double time)
    {
        ScopedRenderStates2D t2d(BlendState::Additive);

        auto t = s3d::Saturate(time);

        switch (m_type) {
        case Type1:
        {
            auto pos = m_pos;
            pos.y += 10.0 * t;
            auto color = static_cast<s3d::int32>(t * 10.0) % 2 ? s3d::ColorF(1.0, 0.5) : s3d::ColorF(0.9);
            m_texture(U"kirakira")(0, 0, 13, 13)
                .scaled(s3d::Periodic::Triangle0_1(0.5s, t) * (1 - t), (1 - t))
                .drawAt(pos, color);
        }
        break;
        case Type2:
        {
            m_texture(U"kirakira")(0, 13, 13, 13)
                .scaled(0.2 + 0.8 * s3d::Periodic::Triangle0_1(1.0s, t))
                .drawAt(m_pos);
        }
        break;
        default:
            break;
        }
        return time <= 1.0;
    }

}
