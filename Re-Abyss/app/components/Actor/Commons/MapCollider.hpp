#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IPrePhysics.hpp>
#include <abyss/components/Actor/base/IPostPhysics.hpp>
#include <abyss/concepts/Component.hpp>
#include <abyss/modules/Actor/base/Tag.hpp>
#include <abyss/types/CShape.hpp>
#include <abyss/types/ColDirection.hpp>

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
        class Result;
    private:
        ActorObj* m_pActor;
        Ref<Body> m_body;
        Ref<ICollider> m_collider;

        Ref<Foot> m_foot;
        std::unique_ptr<Result> m_result;

       bool m_isEnableRoomHit = false;
       s3d::Optional<ColDirection> m_roomHitStrict;
       bool m_isThrough = false; // すりぬけるか
       bool m_useBody = true;
       bool m_isEnableMoveHistory = false;
       s3d::Optional<CShape> m_colliderCache;
    public:
        /// <summary>
        /// MapCollider
        /// </summary>
        /// <param name="pActor"></param>
        /// <param name="useBody">Bodyを使用するか、使わない場合はICollider判定</param>
        MapCollider(ActorObj* pActor, bool useBody = true);

        void onStart() override;

        CShape calcCollider() const;
        CShape getCollider() const;

        void onPrePhysics() override;

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

        MapCollider& setIsEnableMoveHistory(bool enable)
        {
            m_isEnableMoveHistory = enable;
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