#include <abyss/views/Loading/Common/LoadingView.hpp>

#include <abyss/commons/FontName.hpp>
#include <abyss/params/Loading/Common/Param.hpp>
#include <abyss/views/util/Pivot/PivotUtil.hpp>

#include <Siv3D.hpp>

namespace abyss::Loading::Common
{
    LoadingView::LoadingView():
        m_slime(std::make_unique<Actor::Enemy::Slime::SlimeVM>(Resource::Assets::Norelease()))
    {}
    LoadingView& LoadingView::setProgress(double progress)
    {
        m_progress = s3d::Saturate(progress);
        return *this;
    }
    void LoadingView::draw() const
    {
        s3d::Scene::Rect().draw(Palette::Black);
        // Slime君
        {
            using Slime = Param::Slime;
            ScopedColorAdd2D scopedColorAdd(ColorF(1,0));

            Vec2 pos = PivotUtil::FromBr(Slime::BasePos);

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

        // Loading
        {
            using Text = Param::Text;

            const double periodicSec = Text::PeriodicSec;
            const auto jumpTime = Periodic::Sawtooth0_1(periodicSec, Scene::Time() + Text::JumpPeriodicOffset) * periodicSec;
            const auto jumpIndex = jumpTime * Text::JumpIndexCoef;

            const auto rotateTime = Periodic::Sawtooth0_1(periodicSec, Scene::Time() + Text::RotatePeriodicOffset) * periodicSec;
            const auto rotateIndex = rotateTime * Text::RotateIndexCoef;

            Vec2 basePos = PivotUtil::FromBr(Text::BasePos);

            for (auto&& [index, glyph] : Indexed(FontAsset(FontName::Loading).getGlyphs(U"NOW LOADING..."))) {
                auto pos = basePos;
                pos.y -= Text::JumpHeight * Periodic::Jump0_1(1s, Saturate((jumpIndex - index) * Text::JumpTimeRate));
                const auto rotate = Saturate((rotateIndex - index) * Text::RotateTimeRate) * Math::TwoPi;
                TextureRegion tex = glyph.texture;
                auto baseSize = tex.size;
                tex = tex.scaled(Cos(rotate), 1.0);
                pos.x += (baseSize.x - tex.size.x) / 2.0;
                tex.draw(pos + glyph.getOffset(), Palette::White);
                basePos.x += glyph.xAdvance + Text::OffsetX;
            }
        }

        // ProgressBar
        {
            using Bar = Param::ProgressBar;
            Vec2 basePos = PivotUtil::FromBr(Bar::BasePos);
            RectF(basePos, Vec2{Bar::Size.x * m_progress, Bar::Size.y}).draw();
            RectF(basePos, Bar::Size).drawFrame();
        }
    }
}
