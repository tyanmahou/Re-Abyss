//#include "PlayerShotView.hpp"
#include "PlayerShotViewModel.hpp"

#include <Siv3D.hpp>
#include <abyss/models/actors/Player/Shot/PlayerShotActor.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/effects/PlayerShotEffect.hpp>
#include <abyss/models/WorldModel.hpp>

namespace
{
    using namespace abyss;
    PlayerShotViewModel ToViewModel(const PlayerShotActor& actor)
    {
        return PlayerShotViewModel{
            .type = actor.getType(),
            .pos = actor.getPos(),
            .r = actor.getColliderCircle().r,
            .forward = actor.getForward(),
        };
    }

    Color TypeToColor(PlayerShotActor::Type type)
    {
        using namespace Constants::Player;
        static const std::unordered_map<PlayerShotActor::Type, Color> colorMap{
            {PlayerShotActor::Type::Normal, ColorF(1)},
            {PlayerShotActor::Type::Small, ColorF(1)},
            {PlayerShotActor::Type::Medium, MediumChargeColorBase},
            {PlayerShotActor::Type::Big, BigChargeColorBase},
        };
        return colorMap.at(type);
    }
}
namespace abyss
{
    PlayerShotView::PlayerShotView(const PlayerShotActor* const pModel) :
        IActorView(pModel),
        m_pModel(pModel),
        m_texture(U"work/player/player_shot.png")
    {}

    void PlayerShotView::start()
    {
        const auto [type, pos, r, _] = ::ToViewModel(*m_pModel);

        // effect
        if (type != PlayerShotActor::Type::Normal) {
            m_pWorldView->addEffect<PlayerShotFiringEffect>(pos, r, ::TypeToColor(type));
        }
    }

    void PlayerShotView::draw() const
    {
        using Type = PlayerShotActor::Type;

        const auto [type, pos, r, forward] = ::ToViewModel(*m_pModel);

        // effect
        if (Scene::FrameCount() % 2 && (type == PlayerShotActor::Type::Big || type == PlayerShotActor::Type::Medium)) {
            m_pWorldView->addEffect<PlayerShotEffect>(pos, r, ::TypeToColor(type));
        }

        double x = 0, y = 0;
        double size = 0;
        double timer = Periodic::Sawtooth0_1(0.3s);
        if (type == Type::Normal) {
            y = 10 * static_cast<int>(timer * 2);
            size = 10;
        } else if (type == Type::Small) {
            x = 10;
            y = 20 * static_cast<int>(timer * 2);
            size = 20;
        } else if (type == Type::Medium) {
            x = 30 + 40 * static_cast<int>(timer * 4);
            size = 40;
        } else {
            x = 60 * static_cast<int>(timer * 4);
            y = 40;
            size = 60;
        }
        auto tile = m_texture(x, y, size, size);
        (forward == Forward::Right ? tile : tile.mirrored()).drawAt(pos);
    }
}
