#pragma once

#include <Siv3D.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss
{
    class FootModel;
}

namespace abyss::Player
{
    class ChargeModel;
}
namespace abyss::Player
{
    class PlayerActor :
        public IActor,
        public Receiver
    {
    private:
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;
    public:
        PlayerActor();
        void start()override;

        CShape getCollider() const;

        void setPos(const Vec2& pos);
        const Vec2& getPos() const;
        void setForward(const Forward& forward);
        Forward getForward() const;

        RectF region() const;

        bool isDead() const;
        bool accept(const ActVisitor& visitor) override;

        static std::shared_ptr<PlayerActor> Create();
    };
}