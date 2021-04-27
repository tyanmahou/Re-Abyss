#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IPhysics.hpp>
#include <abyss/components/Actor/base/IPrePhysics.hpp>
#include <abyss/components/Actor/base/IPostPhysics.hpp>
#include <abyss/concepts/Component.hpp>
#include <abyss/components/Actor/Commons/Terrain.hpp>
#include <abyss/modules/Actor/base/Tag.hpp>

namespace abyss::Actor
{
    class Foot;

    class MapCollider:
        public IComponent,
        public IPrePhysics,
        public IPhysics,
        public IPostPhysics
    {
    private:
        class Result;
    private:
        Ref<Body> m_body;
        Ref<ICollider> m_collider;

        Ref<Foot> m_foot;
        std::unique_ptr<Result> m_result;

       bool m_isEnableRoomHit = false;
       s3d::Optional<ColDirection> m_roomHitStrict;
       bool m_isThrough = false; // すりぬけるか
       bool m_useBody = true;
    public:
        /// <summary>
        /// MapCollider
        /// </summary>
        /// <param name="pActor"></param>
        /// <param name="useBody">Bodyを使用するか、使わない場合はICollider判定</param>
        MapCollider(ActorObj* pActor, bool useBody = true);

        void onStart() override;

        CShape getCollider() const override;

        void onPrePhysics() override;

        void onCollision(const Ref<Terrain>& terrain) override;

        void onPostPhysics() override;

        MapCollider& setIsEnableRoomHit(bool enable, const s3d::Optional<ColDirection>& strict = s3d::none)
        {
            m_isEnableRoomHit = enable;
            m_roomHitStrict = strict;
            return *this;
        }

        MapCollider& setIsThrough(bool isThrough)
        {
            m_isThrough = isThrough;
            return *this;
        }

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
        const s3d::Array<Ref<Terrain>>& getHitTerrains() const;

        /// <summary>
        /// 衝突した地形をアクターとして取得
        /// </summary>
        /// <returns></returns>
        s3d::Array<ActorObj*> getHitActors()const;

        /// <summary>
        /// 衝突した地形いずれかに対して処理を行う
        /// </summary>
        template<Tag::Tagged T, IsComponent C>
        bool anyThen(std::function<bool(C&)> callback) const
        {
            for (const auto& terrain : this->getHitTerrains()) {
                if (!terrain) {
                    continue;
                }
                if (terrain->isThen<T, C>(callback)) {
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// 衝突した地形すべてに対して処理を行う
        /// </summary>
        template<Tag::Tagged T, IsComponent C>
        bool eachThen(std::function<bool(C&)> callback) const
        {
            bool result = false;
            for (const auto& terrain : this->getHitTerrains()) {
                if (!terrain) {
                    continue;
                }
                result |= terrain->isThen<T, C>(callback);
            }
            return result;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::MapCollider>
    {
        using Base = MultiComponents<
            Actor::IPrePhysics,
            Actor::IPhysics,
            Actor::IPostPhysics
        >;
    };
}