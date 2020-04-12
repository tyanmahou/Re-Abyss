#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss
{
    class SchieldShotActor :
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
        StateManager<SchieldShotActor> m_state;
        std::shared_ptr<SchieldShotVM> m_view;
    public:
        SchieldShotActor(const s3d::Vec2& pos, const s3d::Vec2& dir);

        void update(double dt) override;
        CShape getCollider() const override;
        s3d::Circle getColliderCircle() const;

        void onCollisionStay(ICollider* col) override;

        bool accept(const ActVisitor& visitor) override;
        void draw() const override;

        SchieldShotVM* getBindedView()const;

    };
}