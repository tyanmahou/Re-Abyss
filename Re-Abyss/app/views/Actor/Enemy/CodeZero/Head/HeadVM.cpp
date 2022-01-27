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
    HeadVM& HeadVM::setForward(Forward forward)
    {
        m_forward = forward;
        return *this;
    }
    HeadVM& HeadVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void HeadVM::draw() const
    {
        auto tex = [&]() {
            if (m_forward == Forward::None) {
                return m_texture(U"head")(0, 0, 100, 100);
            }
            return m_texture(U"head")(100, 0, 100, 100).mirrored(m_forward == Forward::Right);
        }();

        tex.drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, m_time));
    }
}
