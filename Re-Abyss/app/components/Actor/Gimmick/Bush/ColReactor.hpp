#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Common/ITimeScale.hpp>
#include <abyss/components/Actor/base/IPostCollision.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Gimmick::Bush
{
    class ColReactor :
        public IComponent,
        public IPostCollision,
        public ITimeScale
    {
    public:
        ColReactor(ActorObj* pActor);
        void onStart() override;
        void onPostCollision()override;
        double getResizeRate() const;
        double timeScale() override;
    private:
        ActorObj* m_pActor;
        Ref<ColCtrl> m_cols;
        double m_resizeRate = 0;
        double m_timeScale = 1.0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Gimmick::Bush::ColReactor>
    {
        using Base = MultiComponents<
            Actor::IPostCollision,
            ITimeScale
        >;
    };
}