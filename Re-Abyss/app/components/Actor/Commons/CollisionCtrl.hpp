#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/Component.hpp>
#include <abyss/modules/Actor/base/Tag.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/ICollision.hpp>
#include <abyss/components/Actor/base/IPreCollision.hpp>
#include <abyss/modules/World/LayerGroup.hpp>

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
        CollisionCtrl(ActorObj* pActor);
        ~CollisionCtrl();
        void setup(Executer executer) override;

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
        s3d::Array<ActorObj*> getHitActors()const;

        /// <summary>
        /// 特定のタグに衝突したか
        /// </summary>
        template<TaggedOf<Tag::ActorTagKind> T>
        bool isHitBy() const
        {
            for (const auto& col : this->getResults()) {
                if (!col) {
                    continue;
                }
                if (col->getActor()->getTag().is<T>()) {
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// 衝突したいずれかに対して処理を行う
        /// </summary>
        template<TaggedOf<Tag::ActorTagKind> T, IsComponent C>
        bool anyThen(std::function<bool(C&)> callback) const
        {
            for (const auto& col : this->getResults()) {
                if (!col) {
                    continue;
                }
                if (col->getActor()->isThen<T, C>(callback)) {
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// 衝突したすべてに対して処理を行う
        /// </summary>
        template<TaggedOf<Tag::ActorTagKind> T, IsComponent C>
        bool eachThen(std::function<bool(C&)> callback) const
        {
            bool result = false;
            for (const auto& col : this->getResults()) {
                if (!col) {
                    continue;
                }
                result |= col->getActor()->isThen<T, C>(callback);
            }
            return result;
        }
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

