#include <abyss/views/Effect/Actor/Ooparts/Common/KiraKira/KiraKiraVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Ooparts::KiraKira
{
    KiraKiraVM::KiraKiraVM(Type type):
        m_texture(Resource::Assets::Main()->loadTexturePacker(U"actors/Common/common_effects.json")(U"kirakira")),
        m_type(type)
    {}

    void KiraKiraVM::draw() const
    {
        ScopedRenderStates2D t2d(BlendState::Additive);
        switch (m_type) {
        case Type::Type1:
        {
            auto pos = m_pos;
            pos.y += 10.0 * m_time;
            auto color = static_cast<s3d::int32>(m_time * 10.0) % 2 ? s3d::ColorF(1.0, 0.5) : s3d::ColorF(0.9);
            m_texture(0, 0, 13, 13)
                .scaled(s3d::Periodic::Triangle0_1(0.5s, m_time) * (1 - m_time), (1 - m_time))
                .drawAt(pos, color);
        }
        break;
        case Type::Type2:
        {
            m_texture(0, 13, 13, 13)
                .scaled(0.2 + 0.8 * s3d::Periodic::Triangle0_1(1.0s, m_time))
                .drawAt(m_pos);
        }
        break;
        default:
            break;
        }
    }
}
