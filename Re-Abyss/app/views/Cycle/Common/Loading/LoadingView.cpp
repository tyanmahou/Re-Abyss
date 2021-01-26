#include "LoadingView.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    LoadingView::LoadingView():
        m_slime(std::make_unique<Actor::Enemy::Slime::SlimeVM>())
    {}
    void LoadingView::draw() const
    {
        s3d::Scene::Rect().draw(Palette::Black);
        {
            ScopedColorAdd2D scopedColorAdd(ColorF(1,0));

            Vec2 pos{ 630, 500 };

            constexpr double periodicSec = 1.3;
            constexpr double jumpSec = 1.0;
            auto t = Periodic::Sawtooth0_1(periodicSec) * periodicSec;
            if (t <= jumpSec) {
                pos.y -= 80 * Periodic::Jump0_1(jumpSec, t);
            }
            m_slime
                ->setPos(pos)
                .setForward(Forward::Left)
                .setTime(s3d::Math::Lerp(0.0, 1.0, (t - jumpSec) / (periodicSec - jumpSec)));
            if (t <= jumpSec) {
                m_slime
                    ->setVelocity(t <= jumpSec / 2.0 ? Vec2{ 0, -1 } : Vec2{0, 1})
                    .drawJump();
            } else {
                m_slime->drawWalk();
            }
        }
    }
}
