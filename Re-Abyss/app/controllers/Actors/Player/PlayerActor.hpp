#pragma once

#include <Siv3D.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/FootModel.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/models/Actors/Player/ChargeModel.hpp>
#include <abyss/models/Actors/base/OldStateModel.hpp>

namespace abyss::Player
{
    class PlayerVM;

    class PlayerActor :
        public IActor,
        public Receiver
    {
    public:
        enum class State
        {
            Swim,
            Damage,
            Ladder,
            Dead,
        };
    private:
        Ref<BodyModel> m_body;
        Ref<FootModel> m_foot;
        Ref<ChargeModel> m_charge;
        Ref<HPModel> m_hp;


        Ref<OldStateModel<PlayerActor>> m_state;
        std::shared_ptr<PlayerVM> m_view;

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
        PlayerVM* getBindedView()const;

        static std::shared_ptr<PlayerActor> Create();
    };
}