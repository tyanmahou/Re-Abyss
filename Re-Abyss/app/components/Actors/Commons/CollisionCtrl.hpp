#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ICollision.hpp>
#include <abyss/components/Actors/base/IPreCollision.hpp>

namespace abyss::Actor
{
    class CollisionCtrl final:
        public IComponent,
        public IPreCollision,
        public ICollision
    {
    private:
        class Result;
    public:
        CollisionCtrl(IActor* pActor);

        void setup(Depends depends) override;

        void onStart() override;

        CShape getCollider() const override;

        void onPreCollision() override;
        void onCollision(const Ref<ICollision>& other) override;

        /// <summary>
        /// 衝突を取得
        /// </summary>
        /// <returns></returns>
        const s3d::Array<Ref<ICollision>>& getResults() const;

        /// <summary>
        /// 衝突したアクターとして取得
        /// </summary>
        /// <returns></returns>
        s3d::Array<IActor*> getHitActors()const;
    private:
        Ref<ICollider> m_collider;
        std::unique_ptr<Result> m_result;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Actor::CollisionCtrl>
    {
        using Base = MultiComponents<
            Actor::IPreCollision,
            Actor::ICollision
        >;
    };
}

