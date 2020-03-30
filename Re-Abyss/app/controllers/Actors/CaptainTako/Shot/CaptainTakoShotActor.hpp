#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss
{
    class CaptainTakoShotActor:
        public IActor,
        public Attacker
    {
    public:
        enum State
        {
            Base
        };
    private:
        BodyModel m_body;
        StateManager<CaptainTakoShotActor> m_state;
        std::shared_ptr<CaptainTakoShotVM> m_view;
    public:
        CaptainTakoShotActor(const s3d::Vec2& pos, Forward forward);

        void start() override;
        void update(double dt) override;
        CShape getCollider() const override;
        void onCollisionStay(ICollider* col) override;

        s3d::Circle getColliderCircle() const;

        bool accept(const ActVisitor& visitor) override;
        void draw() const override;

        CaptainTakoShotVM* getBindedView()const;

    };
}