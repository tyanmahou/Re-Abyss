#include <abyss/views/Actor/Enemy/BazookaKun/BazookaKunVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    BazookaKunVM::BazookaKunVM() :
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/BazookaKun/BazookaKun.json"))
    {}

    BazookaKunVM& BazookaKunVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    BazookaKunVM& BazookaKunVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }
    void BazookaKunVM::draw() const
    {
        RectF rect{ m_pos - Vec2{45, 30}, Vec2{90, 60} };
        auto quad = rect.rotatedAt(rect.bl(), s3d::ToRadians(m_rotate));

        auto tex = m_texture(U"body")
            .mirrored(m_isMirrored)
            .flipped(m_isFlipped);
        quad(tex).draw();
    }
}
