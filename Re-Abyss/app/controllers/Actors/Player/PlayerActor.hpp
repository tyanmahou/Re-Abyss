#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss
{
    class Foot;
}

namespace abyss::Actor::Player
{
    class ChargeCtrl;
}
namespace abyss::Actor::Player
{
    class PlayerActor :
        public IActor
    {
    private:
        Ref<Body> m_body;
        Ref<HP> m_hp;
    public:
        PlayerActor();

        CShape getCollider() const;

        void setPos(const s3d::Vec2& pos);
        const s3d::Vec2& getPos() const;
        void setForward(const Forward& forward);
        Forward getForward() const;

        s3d::RectF region() const;

        bool isDead() const;

        static std::shared_ptr<PlayerActor> Create();
    };
}