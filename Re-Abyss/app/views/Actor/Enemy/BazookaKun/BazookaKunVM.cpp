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
        this->drawBazooka();
        this->drawBody();
        this->drawEye();
    }
    s3d::Quad BazookaKunVM::quad() const
    {
        RectF rect{ m_pos - Vec2{45, 30}, Vec2{90, 60} };
        return rect.rotatedAt(rect.bl(), s3d::ToRadians(m_rotate));
    }
    void BazookaKunVM::drawBazooka() const
    {
        RectF rect{ m_pos - Vec2{45, 30}, Vec2{90, 60} };
        auto quad = rect.rotatedAt(rect.bl(), s3d::ToRadians(m_rotate));
        quad.moveBy(Vec2{ m_isMirrored ? -1 : 1, 0 }.rotate(s3d::ToRadians(m_rotate)) * -10);
        {
            auto center = rect.center();
            auto pivot = center + Vec2{ m_isMirrored ? -3 : 3, m_isFlipped ? -15 : 15 };
            pivot = pivot.rotateAt(rect.bl(), s3d::ToRadians(m_rotate));

            quad = quad.rotatedAt(pivot, s3d::ToRadians(m_bazookaRotate));
        }

        auto tex = m_texture(U"bazooka")
            .mirrored(m_isMirrored)
            .flipped(m_isFlipped);
        quad(tex).draw();
    }
    void BazookaKunVM::drawBody() const
    {
        auto quad = this->quad();

        auto tex = m_texture(U"body")
            .mirrored(m_isMirrored)
            .flipped(m_isFlipped);
        quad(tex).draw();
    }
    void BazookaKunVM::drawEye() const
    {
        s3d::int32 frame = static_cast<int32>(m_time * 60.0) % 240 <= 10 ? 1 : 0;

        auto quad = this->quad();
        {
            RectF rect{ m_pos - Vec2{45, 30}, Vec2{90, 60} };
            auto center = rect.center();
            auto pivot = center + Vec2{ m_isMirrored ? 3 : -3, m_isFlipped ? -15 : 15 };
            pivot = pivot.rotateAt(rect.bl(), s3d::ToRadians(m_rotate));

            quad = quad.rotatedAt(pivot, s3d::ToRadians(m_bazookaRotate));
        }
        auto tex = m_texture(frame == 1 ? U"eye2" : U"eye")
            .mirrored(m_isMirrored)
            .flipped(m_isFlipped);
        quad(tex).draw();
    }
}
