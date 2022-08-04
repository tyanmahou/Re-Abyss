#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
    class EyeCtrl final :
        public IComponent,
        public ILastUpdate
    {
    public:
        EyeCtrl(ActorObj* pActor);

        void setup(Executer executer) override;
        void onStart() override;

        void onLastUpdate() override;

        const s3d::Vec2& getEyePosL() const
        {
            return m_eyePosL;
        }
        const s3d::Vec2& getEyePosR() const
        {
            return m_eyePosR;
        }
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;

        s3d::Vec2 m_eyePosL{ 0, 0 };
        s3d::Vec2 m_eyePosR{ 0, 0 };
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::BabyDux::EyeCtrl>
    {
        using Base = MultiComponents<
            Actor::ILastUpdate
        >;
    };
}
