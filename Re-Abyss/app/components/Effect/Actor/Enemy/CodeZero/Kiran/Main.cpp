#include <abyss/components/Effect/Actor/Enemy/CodeZero/Kiran/Main.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::Kiran
{
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos) :
        m_pObj(pObj),
        m_pos(pos),
        m_texture(Resource::Assets::Main()->load(U"Effect/Actor/Common/CommonEffects.json"))
    {}

    void Main::onUpdate()
    {
    }

    bool Main::onDraw(double time)
    {
        s3d::ScopedRenderStates2D blend(s3d::BlendState::Additive);

        auto rate = s3d::EaseOutQuart(s3d::Min(time / 2.0, 1.0));
        auto alpha = 1.0 - s3d::Math::Lerp(0.0, 1.0, s3d::Max(time - 1.0, 0.0));
        const ColorF color(1, alpha);
        Circle(m_pos, 10.0 * rate).drawFrame(2.0, color);
        {
            const auto angleRad = rate * 560_deg + 50_deg;
            auto baseTex = m_texture(U"kiran").scaled(rate * 2.5, rate * 0.5);
            baseTex.rotated(angleRad).drawAt(m_pos, color);
            baseTex.rotated(angleRad + 90_deg).drawAt(m_pos, color);
        }
        return time <= 2.0;
    }
}