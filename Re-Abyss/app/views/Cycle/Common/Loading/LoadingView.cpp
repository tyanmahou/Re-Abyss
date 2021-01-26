#include "LoadingView.hpp"
#include <abyss/commons/FontName.hpp>
#include <abyss/params/Cycle/Common/LoadingParam.hpp>
#include <Siv3D.hpp>

namespace abyss::Cycle
{
    LoadingView::LoadingView():
        m_slime(std::make_unique<Actor::Enemy::Slime::SlimeVM>())
    {}
    void LoadingView::draw() const
    {
        s3d::Scene::Rect().draw(Palette::Black);
        // Slime君
        {
            using Slime = LoadingParam::Slime;
            ScopedColorAdd2D scopedColorAdd(ColorF(1,0));

            Vec2 pos = Slime::BasePos;

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
                    .drawJump();
            } else {
                m_slime->drawWalk();
            }
        }

        // Loading
        {
            using Text = LoadingParam::Text;

            const double periodicSec = Text::PeriodicSec;
            const auto t = Periodic::Sawtooth0_1(periodicSec, Scene::Time() + Text::JumpPeriodicOffset) * periodicSec;

            const auto jumpIndex = t * Text::JumpIndexCoef;
            Vec2 basePos = LoadingParam::Text::BasePos;
            for (auto&& glyph : FontAsset(FontName::Loading)(U"NOW LOADING...")) {
                auto pos = basePos;
                pos.y -= Text::JumpHeight * Periodic::Jump0_1(1s, Saturate((jumpIndex - glyph.index) * Text::JumpTimeRate));

                glyph.texture.draw(pos + glyph.offset, Palette::White);
                basePos.x += glyph.xAdvance + LoadingParam::Text::OffsetX;
            }
        }
    }
}
