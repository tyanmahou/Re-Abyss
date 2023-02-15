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
    BodyVM& BodyVM::setWindLPos(const s3d::Vec2& pos)
    {
        m_windLPos = s3d::Round(pos);
        return *this;
    }
    BodyVM& BodyVM::setWindRPos(const s3d::Vec2& pos)
    {
        m_windRPos = s3d::Round(pos);
        return *this;
    }
    void BodyVM::draw() const
    {
        m_texture(U"wind").drawAt(m_windLPos, m_colorMul);
        m_texture(U"wind").mirrored().drawAt(m_windRPos, m_colorMul);
        m_texture(U"body").drawAt(m_pos, m_colorMul);
    }

}
