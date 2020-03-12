//#include "PlayerView.hpp"
#include "PlayerViewModel.hpp"

#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>

namespace
{
    using namespace abyss;

    PlayerViewModel ToViewModel(const PlayerActor& actor)
    {
        return PlayerViewModel{
            .motion = actor.getMotion(),
            .pos = s3d::Math::Ceil(actor.getPos()),
            .vellocity = actor.getVellocity(),
            .forward = actor.getForward(),

            .charge = actor.getCharge(),
        };
    }
}
namespace abyss
{
    void PlayerView::drawPlayer() const
    {
        const auto [motion, pos, v, forward, _] = ::ToViewModel(*m_pModel);
        int timer = Scene::FrameCount();
        bool isRight = forward == Forward::Right;

        switch (motion) {
        case PlayerActor::Motion::Stay:
        {
            int page = timer % 240 <= 10 ? 1 : 0;
            m_texture(U"player_stay.png", { isRight ? 40 : 0, 80 * page }, { 40, 80 }).drawAt(pos);
        }break;
        case PlayerActor::Motion::Float:
        {
            double y = 160;
            if (v.y < -1.6) {
                y = 0;
            } else if (v.y < -0.8) {
                y = 80;
            } else {
                y = 80 * (timer / 30 % 2) + 160;
            }

            m_texture(U"player_float.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(pos);
        }break;
        case PlayerActor::Motion::Run:
        {
            int x = static_cast<int>(Periodic::Triangle0_1(1.2s) * 5) * 60;
            m_texture(U"player_run.png", { x, isRight ? 80 : 0 }, { 60, 80 }).drawAt(pos);
        }break;
        case PlayerActor::Motion::Swim:
        {
            double y = 0;
            if (v.y < -1.6) {
                y = 160;
            } else if (v.y < -0.8) {
                y = 240;
            } else {
                y = 80 * (timer / 30 % 2);
            }
            m_texture(U"player_swim.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(pos);
        }break;
        case PlayerActor::Motion::Dive:
        {
            double y = 80 * (timer / 30 % 2);
            m_texture(U"player_dive.png", { isRight ? 60 : 0, y }, { 60, 80 }).drawAt(pos);
        }break;
        case PlayerActor::Motion::Damge:
        {
            Color c = timer / 6 % 2 ? Color(255, 128, 128, 128) : Palette::White;
            m_texture(U"player_damage.png", { isRight ? 60 : 0, 0 }, { 60, 80 }).drawAt(pos, c);
        }break;
        case PlayerActor::Motion::Ladder:
        {
            m_texture(U"player_ladder.png", { 40 * (static_cast<int>(pos.y / 30) % 2), 0 }, { 40, 80 }).drawAt(pos);
        }break;
        case PlayerActor::Motion::LadderTop:
        {
            m_texture(U"player_ladder.png", { 80, 0 }, { 40, 80 }).drawAt(pos);
        }break;
        case PlayerActor::Motion::Door:
        {

            m_texture(U"player_door.png", { 40 * static_cast<int>(Periodic::Sawtooth0_1(1s) * 2), 0 }, { 40, 80 }).drawAt(pos);
        }break;
        default:
            break;
        }
    }
    void PlayerView::drawCharge() const
    {
        const auto viewModel = ::ToViewModel(*m_pModel);
        const int32& charge = viewModel.charge;
        const Vec2& pos = viewModel.pos;

        if (charge > 10) {
            ScopedRenderStates2D t2d(BlendState::Additive);
            double a = 0.5 * Periodic::Triangle0_1(0.2s);
            ColorF color;
            if (charge >= Constants::Player::BigCharge) {
                color = Constants::Player::BigChargeColorBase;
            } else if (charge >= Constants::Player::MediumCharge) {
                color = Constants::Player::MediumChargeColorBase;
            } else {
                color = ColorF(1);
            }
            Circle(pos, 80 * (1 - Periodic::Sawtooth0_1(0.6s))).drawFrame(1, 1, color.setA(a));
            double s = 100 * Periodic::Triangle0_1(0.3s);
            RectF({ 0,0,s, s })
                .setCenter(pos)
                .rotated(Math::QuarterPi * Periodic::Square0_1(0.6s))
                .drawFrame(1, 1, color.setA(0.5 - a));

            if (charge >= Constants::Player::BigCharge) {
                Circle(pos, Periodic::Triangle0_1(0.3s) * 30 + 30).draw(color.setA(a));
            } else if (charge >= Constants::Player::MediumCharge) {
                Circle(pos, Periodic::Triangle0_1(0.3s) * 5 + 30).draw(color.setA(a));
            }
        }
    }
    PlayerView::PlayerView(const PlayerActor* const pModel) :
        IActorView(pModel),
        m_pModel(pModel),
        m_texture(U"work/player/player.json")
    {}
    void PlayerView::draw() const
    {
        this->drawPlayer();

        // チャージ
        this->drawCharge();
    }
}