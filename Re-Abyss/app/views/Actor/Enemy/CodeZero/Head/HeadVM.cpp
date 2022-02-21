#include <abyss/views/Actor/Enemy/CodeZero/Head/HeadVM.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
    HeadVM::HeadVM() :
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/CodeZero/CodeZero.json"))
    {}

    HeadVM& HeadVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }

    HeadVM& HeadVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    HeadVM& HeadVM::setLook(const Look& look)
    {
        m_look = look;
        return *this;
    }
    HeadVM& HeadVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void HeadVM::draw() const
    {
        TextureRegion tex = [&]() {
            if (m_look.isForward(Forward::Up)) {
                if (auto f = m_look.horizonalForward(); f != Forward::None) {
                    return m_texture(U"head")(0, 170, 170, 170).mirrored(f == Forward::Right);
                } else {
                    return m_texture(U"head")(0, 340, 170, 170);
                }
            } else if (m_look.isForward(Forward::Down)) {
                if (auto f = m_look.horizonalForward(); f != Forward::None) {
                    return m_texture(U"head")(170, 0, 170, 170).mirrored(f == Forward::Right);
                } else {
                    return m_texture(U"head")(170, 340, 170, 170);
                }
            } else {
                if (auto f = m_look.horizonalForward(); f != Forward::None) {
                    return m_texture(U"head")(170, 170, 170, 170).mirrored(f == Forward::Right);
                }
            }
            return m_texture(U"head")(0, 0, 170, 170);
        }();

        tex.drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, m_time));
    }
}
