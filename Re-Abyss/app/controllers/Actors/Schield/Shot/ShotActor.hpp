#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/base/StateModel.hpp>

namespace abyss::Schield::Shot
{
    class ShotVM;

    class ShotActor :
        public IActor,
        public Attacker
    {
    public:
        enum State
        {
            Base
        };
    private:
        Ref<BodyModel> m_body;
        std::shared_ptr<ShotVM> m_view;
    public:
        ShotActor(const s3d::Vec2& pos, const s3d::Vec2& dir);

        CShape getCollider() const;
        s3d::Circle getColliderCircle() const;

        bool accept(const ActVisitor& visitor) override;

        ShotVM* getBindedView()const;

    };
}