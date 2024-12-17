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
        Transformer2D trans(Mat3x2::Translate(m_pos).rotated(s3d::ToRadians(m_rotate), m_pos));

        this->drawBazooka();
        this->drawBody();
        this->drawEye();
    }
    void BazookaKunVM::drawBazooka() const
    {
        Vec2 pivot = Vec2{ m_isMirrored ? 3 : -3, m_isFlipped ? -15 + Param::Base::Size.y / 2 : 15 - Param::Base::Size.y / 2 };
        Transformer2D trans2(Mat3x2::Rotate(s3d::ToRadians(m_bazookaRotate), pivot));
        Vec2 offset = Vec2{ (m_isMirrored ? 1 : -1) * 10 * m_bazookaAnimRate, 0 };
        auto tex = m_texture(U"bazooka")
            .mirrored(m_isMirrored)
            .flipped(m_isFlipped);
        if (m_isFlipped) {
            tex.draw(Arg::topCenter = offset, m_colorMul);
        } else {
            tex.draw(Arg::bottomCenter = offset, m_colorMul);
        }
    }
    void BazookaKunVM::drawBody() const
    {
        auto tex = m_texture(U"body")
            .mirrored(m_isMirrored)
            .flipped(m_isFlipped);
        if (m_isFlipped) {
            tex.draw(Arg::topCenter = Vec2::Zero(), m_colorMul);
        } else {
            tex.draw(Arg::bottomCenter = Vec2::Zero(), m_colorMul);
        }
    }
    void BazookaKunVM::drawEye() const
    {
        Vec2 pivot = Vec2{ m_isMirrored ? 3 : -3, m_isFlipped ? -15 + Param::Base::Size.y / 2: 15 - Param::Base::Size.y / 2};
        Transformer2D trans2(Mat3x2::Rotate(s3d::ToRadians(m_bazookaRotate), pivot));
        s3d::int32 frame = static_cast<int32>(m_time * 60.0) % 240 <= 10 ? 1 : 0;
        auto tex = m_texture(frame == 1 ? U"eye2" : U"eye")
            .mirrored(m_isMirrored)
            .flipped(m_isFlipped);
        if (m_isFlipped) {
            tex.draw(Arg::topCenter = Vec2::Zero(), m_colorMul);
        } else {
            tex.draw(Arg::bottomCenter = Vec2::Zero(), m_colorMul);
        }
    }
}
