#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IPostCollision.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/base/IDamageCallback.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss::Actor
{
    class DamageCtrl : 
        public IComponent,
        public IPostCollision
    {
    protected:
        Ref<HP> m_hp;
        Ref<CollisionCtrl> m_colCtrl;
        ActorObj* m_pActor;

        bool m_isActive = true;
        s3d::Optional<DamageData> m_damageData;
    public:
        DamageCtrl(ActorObj* pActor);

        void onStart() override;
        void onPostCollision()override;

        void setActive(bool isActive)
        {
            m_isActive = isActive;
        }

        const s3d::Optional<DamageData>& getData() const
        {
            return m_damageData;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DamageCtrl>
    {
        using Base = Actor::IPostCollision;
    };
}