#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IPostCollision.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
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
        IActor* m_pActor;

        bool m_isActive = true;
    public:
        DamageCtrl(IActor* pActor);

        void onStart() override;
        void onPostCollision()override;

        void setActive(bool isActive)
        {
            m_isActive = isActive;
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