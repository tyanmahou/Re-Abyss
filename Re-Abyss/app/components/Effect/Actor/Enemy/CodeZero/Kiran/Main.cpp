#include <abyss/components/Effect/Actor/Enemy/CodeZero/Kiran/Main.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/views/Effect/Actor/Common/KiranVM.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::Kiran
{
    Main::Main(EffectObj* pObj, const s3d::Vec2& pos) :
        m_pObj(pObj),
        m_view(std::make_unique<Actor::KiranVM>())
    {
        m_view->setPos(pos);
    }

    Main::~Main()
    {}

    void Main::onUpdate()
    {
    }

    bool Main::onDraw(double time)
    {
        s3d::ScopedRenderStates2D blend(s3d::BlendState::Additive);

        auto rate = s3d::EaseOutCirc(s3d::Min(time / 2.0, 1.0));
        auto alpha = 1.0 - s3d::Math::Lerp(0.0, 1.0, s3d::Max(time - 1.0, 0.0));
        const ColorF color(1, alpha);
        const auto angleRad = rate * 560_deg + 50_deg;
        m_view
            ->setCircleRadius(10.0 * rate)
            .setRotate(angleRad)
            .setScale(rate * 2.5, rate * 0.5)
            .setColorMul(color)
            .draw();
            ;
        return time <= 2.0;
    }
}