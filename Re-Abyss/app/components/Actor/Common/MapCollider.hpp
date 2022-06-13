#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPrePhysics.hpp>
#include <abyss/components/Actor/base/IPostPhysics.hpp>
#include <abyss/concepts/Component.hpp>
#include <abyss/modules/Physics/base/TerrainData.hpp>
#include <abyss/utils/Collision/CShape.hpp>
#include <abyss/utils/Collision/ColDirection.hpp>

#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
{
    class Foot;

    class MapCollider:
        public IComponent,
        public IPrePhysics,
        public IPostPhysics
    {
    private:
        class Contacter;
        class Result;
    public:
        /// <summary>
        /// MapCollider
        /// </summary>
        /// <param name="pActor"></param>
        /// <param name="useBody">Bodyを使用するか、使わない場合はICollider判定</param>
        MapCollider(ActorObj* pActor, bool useBody = true);

        void onStart() override;
        void onEnd() override;

        void onPrePhysics() override;

        void onPostPhysics() override;

        MapCollider& setIsEnableRoomHit(bool enable, const s3d::Optional<ColDirection>& strict = s3d::none);

        MapCollider& setIsThrough(bool isThrough);

        MapCollider& setIsEnableTrajectory(bool enable);

        /// <summary>
        /// 床とあたったか
        /// </summary>
        /// <returns></returns>
        bool isHitGround() const;

        /// <summary>
        /// 壁と当たったか
        /// </summary>
        /// <returns></returns>
        bool isHitWall() const;

        /// <summary>
        /// 向きを考慮して壁と当たったか
        /// </summary>
        /// <returns></returns>
        bool isHitForwardWall() const;

        /// <summary>
        /// 何かに当たったか
        /// </summary>
        /// <returns></returns>
        bool isHitAny() const;

        /// <summary>
        /// 衝突した地形を取得
        /// </summary>
        /// <returns></returns>
        const s3d::Array<Physics::TerrainData>& getHitTerrains() const;

        /// <summary>
        /// 特定のタグの地形に衝突したか
        /// </summary>
        template<TaggedOf<Physics::Tag::PhysicsTagKind> T>
        bool isHitBy() const
        {
            for (const auto& terrain : this->getHitTerrains()) {
                if (terrain.tag.is<T>()) {
                    return true;
                }
            }
            return false;
        }
    private:
        ActorObj* m_pActor;
        std::shared_ptr<Contacter> m_contacter;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::MapCollider>
    {
        using Base = MultiComponents<
            Actor::IPrePhysics,
            Actor::IPostPhysics
        >;
    };
}