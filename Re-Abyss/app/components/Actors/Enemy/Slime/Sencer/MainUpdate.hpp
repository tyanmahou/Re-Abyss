#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>
#include <abyss/models/Actors/base/IPrePhysicsModel.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::Slime::Sencer
{
    class ParentCtrl;

    class MainUpdate : 
        public IComponent,
        public IUpdateModel,
        public IPrePhysicsModel
    {
        IActor* m_pActor;
        Ref<ParentCtrl> m_parentCtrl;
        Ref<MapCollider> m_mapColl;
        Ref<BodyModel> m_body;
    public:
        MainUpdate(IActor* pActor);
        void setup() override;
        void onUpdate(double dt) override;

        void onPrePhysics() override;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::Slime::Sencer::MainUpdate>
    {
        using Base = MultiComponents<IUpdateModel, IPrePhysicsModel>;
    };
}