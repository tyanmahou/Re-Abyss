#include <abyss/views/Actor/Enemy/CodeZero/Hand/HandVM.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    HandVM::HandVM(Forward forward) :
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/CodeZero/CodeZero.json")),
        m_forward(forward),
        m_rotate(0)
    {}
    HandVM& HandVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    HandVM& HandVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    HandVM& HandVM::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }
    void HandVM::draw() const
    {
        switch (m_motion) {
        case Motion::Wait:
            return this->drawBase();
        case Motion::AttackWait:
            return this->drawAttackWait();
        }
    }
    void HandVM::drawBase(const s3d::Color & color) const
    {
        m_texture(U"hand")
            .mirrored(m_forward == Forward::Right)
            .rotated(m_rotate)
            .drawAt(m_pos, color);
    }
    void HandVM::drawAttackWait()const
    {
        double t = Periodic::Sawtooth0_1(0.2s, m_time);
        HSV hsv(360 * t, 0.5, 1.0);
        this->drawBase(hsv.toColor());
    }
}
