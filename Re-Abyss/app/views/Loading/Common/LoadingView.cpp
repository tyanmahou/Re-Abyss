#include <abyss/views/Loading/Common/LoadingView.hpp>

#include <abyss/commons/FontName.hpp>
#include <abyss/params/Loading/Common/Param.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>

#include <Siv3D.hpp>

namespace abyss::Loading::Common
{
    LoadingView::LoadingView():
        m_slime(std::make_unique<Actor::Enemy::Slime::SlimeVM>(Resource::Assets::Norelease()))
    {}
    void LoadingView::draw() const
    {
        // Slime君
        {
            using Slime = Param::Slime;
            ScopedColorAdd2D scopedColorAdd(ColorF(1,0));

            Vec2 pos = AnchorUtil::FromBr(Slime::BasePos);

            const double periodicSec = Slime::PeriodicSec;
            const double jumpSec = Slime::JumpSec;
            auto t = Periodic::Sawtooth0_1(periodicSec) * periodicSec;
            if (t <= jumpSec) {
                pos.y -= 80 * Periodic::Jump0_1(jumpSec, t);
            }
            m_slime
                ->setPos(pos)
                .setForward(Forward::Left)
                .setTime(0.5 + s3d::Math::Lerp(0.0, 1.0, (t - jumpSec) / (periodicSec - jumpSec)));
            if (t <= jumpSec) {
                m_slime
                    ->setVelocity(t <= jumpSec / 2.0 ? Vec2{ 0, -1 } : Vec2{0, 1})
                    .setMotion(Actor::Enemy::Slime::Motion::Jump)
                    .draw();
            } else {
                m_slime
                    ->setMotion(Actor::Enemy::Slime::Motion::Walk)
                    .draw();
            }
        }
    }
}
