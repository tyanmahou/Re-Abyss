#include <abyss/views/Actor/Enemy/CodeZero/Body/BodyVM.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::CodeZero::Body
{
    BodyVM::BodyVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/CodeZero/CodeZero.json"))
    {}

    BodyVM& BodyVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    BodyVM& BodyVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }
    BodyVM& BodyVM::setWingLPos(const s3d::Vec2& pos)
    {
        m_wingLPos = s3d::Round(pos);
        return *this;
    }
    BodyVM& BodyVM::setWingRPos(const s3d::Vec2& pos)
    {
        m_wingRPos = s3d::Round(pos);
        return *this;
    }
    void BodyVM::draw() const
    {
        ScopedColorMul2D scopedMul(m_colorMul);
        m_texture(U"wing").drawAt(m_wingLPos);
        m_texture(U"wing").mirrored().drawAt(m_wingRPos);
        m_texture(U"body").drawAt(m_pos);
    }

}
