#include <abyss/views/Actor/Enemy/CodeZero/Body/BodyVM.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::CodeZero::Body
{
    BodyVM::BodyVM():
        m_texture(Resource::Assets::Main()->load(U"actors/Enemy/CodeZero/code_zero.json"))
    {}

    BodyVM& BodyVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }

    void BodyVM::draw() const
    {
        m_texture(U"body").drawAt(m_pos);
    }

}
