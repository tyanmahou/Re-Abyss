#include <abyss/views/Actor/Enemy/KingDux/Foot/FootVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::Foot
{
    FootVM::FootVM() :
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/KingDux/KingDux.json"))
    {}
    FootVM& FootVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    FootVM& FootVM::setAnimTime(double time)
    {
        m_animTime = time;
        return *this;
    }
    FootVM& FootVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        return *this;
    }
    FootVM& FootVM::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }
    FootVM& FootVM::setIsFlip(bool isFlip)
    {
        m_isFlip = isFlip;
        return *this;
    }
    FootVM& FootVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }
    FootVM& FootVM::setColorAdd(const s3d::ColorF color)
    {
        m_colorAdd = color;
        return *this;
    }
    void FootVM::draw() const
    {
        auto color = m_colorMul;
        s3d::ScopedColorAdd2D addColor(m_colorAdd);
        if (m_motion == Motion::Dead) {
            color.a *= s3d::Saturate(1.0 - m_animTime);
        }
        // 足
        const auto& pageMap = Param::Foot::AnimFrameMap;
        const s3d::uint32 pageSize = static_cast<s3d::uint32>(pageMap.size());
        auto pageRate = s3d::Periodic::Triangle0_1(Param::Foot::AnimTimeSec, m_time);
        if (pageRate >= 0.5) {
            pageRate = 2.0 / 3.0 * (pageRate * pageRate) + (1.0 / 3.0);
        }
        const auto pageIndex = static_cast<s3d::uint32>(pageRate * pageSize) % pageSize;

        const auto page = pageMap[pageIndex];

        auto scaleRate = s3d::Periodic::Triangle0_1(2.0, m_time);
        auto scale = 1.0 + s3d::Math::Lerp(0.0, 0.1, scaleRate);
        constexpr auto size = s3d::Vec2{ 300, 180 };
        const auto scaledSize = size * scale;
        m_texture(U"foot")(page % 3 * 300, page / 3 * 180, size)
            .resized(scaledSize)
            .flipped(m_isFlip)
            .rotated(m_rotate)
            .draw(s3d::Round(m_pos - scaledSize / 2.0), color);
    }
}
