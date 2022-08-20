#include <abyss/views/Actor/Enemy/BazookaKun/BazookaKunVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/BazookaKun/Param.hpp>
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
        RectF rect{ m_pos - Param::Base::Size / 2, Param::Base::Size };
        return rect.rotated(s3d::ToRadians(m_rotate));
    }
    void BazookaKunVM::drawBazooka() const
    {
        auto quad = this->quad();
        quad.moveBy(Vec2{ m_isMirrored ? 1 : -1, 0 }.rotated(s3d::ToRadians(m_rotate)) * 10 * m_bazookaAnimRate);
        {
            auto pivot = m_pos + Vec2{ m_isMirrored ? -3 : 3, m_isFlipped ? -15 : 15 };
            pivot = pivot.rotateAt(m_pos, s3d::ToRadians(m_rotate));

            quad = quad.rotatedAt(pivot, s3d::ToRadians(m_bazookaRotate));
        }

        auto tex = m_texture(U"bazooka")
            .mirrored(m_isMirrored)
            .flipped(m_isFlipped);
        quad(tex).draw();
    }
    void BazookaKunVM::drawBody() const
    {
        m_texture(U"body")
            .mirrored(m_isMirrored)
            .flipped(m_isFlipped)
            .rotated(s3d::ToRadians(m_rotate))
            .drawAt(m_pos)
            ;
    }
    void BazookaKunVM::drawEye() const
    {
        s3d::int32 frame = static_cast<int32>(m_time * 60.0) % 240 <= 10 ? 1 : 0;

        auto quad = this->quad();
        {
            auto pivot = m_pos + Vec2{ m_isMirrored ? 3 : -3, m_isFlipped ? -15 : 15 };
            pivot = pivot.rotateAt(m_pos, s3d::ToRadians(m_rotate));

            quad = quad.rotatedAt(pivot, s3d::ToRadians(m_bazookaRotate));
        }
        auto tex = m_texture(frame == 1 ? U"eye2" : U"eye")
            .mirrored(m_isMirrored)
            .flipped(m_isFlipped);
        quad(tex).draw();
    }
}
