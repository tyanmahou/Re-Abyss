#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IPhysics.hpp>
#include <abyss/components/Actors/base/IPrePhysics.hpp>
#include <abyss/components/Actors/base/ILastPhysics.hpp>

namespace abyss::Actor
{
    class Foot;

    class MapCollider:
        public IComponent,
        public IPrePhysics,
        public IPhysics,
        public ILastPhysics
    {
    private:
        class Result;
    private:
        Ref<Body> m_body;
        Ref<Foot> m_foot;
        std::unique_ptr<Result> m_result;

       bool m_isEnableRoomHit = false;
       bool m_isEnableRoomHitStrict = false;
       bool m_isThrough = false; // すりぬけるか
    public:

        MapCollider(IActor* pActor);

        void setup() override;

        s3d::RectF getCollider() const override;

        void onPrePhysics() override;

        void onCollision(const Ref<Terrain>& terrain) override;

        void onLastPhysics() override;

        MapCollider& setIsEnableRoomHit(bool enable, bool isStrict = false)
        {
            m_isEnableRoomHit = enable;
            m_isEnableRoomHitStrict = isStrict;
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


        bool acceptAll(const ActVisitor& visitor);

        /// <summary>
        /// 衝突した地形を取得
        /// </summary>
        /// <returns></returns>
        const s3d::Array<Ref<Terrain>>& getHitTerrains() const;

        /// <summary>
        /// 衝突した地形をアクターとして取得
        /// </summary>
        /// <returns></returns>
        s3d::Array<IActor*> getHitActors()const;

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
            Actor::ILastPhysics
        >;
    };
}