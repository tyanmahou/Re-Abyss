#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IPhysicsModel.hpp>
#include <abyss/models/Actors/base/IPrePhysicsModel.hpp>
#include <abyss/models/Actors/base/ILastPhysicsModel.hpp>

namespace abyss
{
    class MapColliderModel:
        public IComponent,
        public IPrePhysicsModel,
        public IPhysicsModel,
        public ILastPhysicsModel
    {
    private:
        class Result;
    private:
        Ref<BodyModel> m_body;
       std::unique_ptr<Result> m_result;

       bool m_enableRoomHit = false;
       bool m_isThrough = false; // すりぬけるか
    public:

        MapColliderModel(IActor* pActor);

        void setup() override;

        s3d::RectF getCollider() const override;

        void onPrePhysics() override;

        void onCollision(const Ref<TerrainModel>& terrain) override;

        void onLastPhysics() override;

        MapColliderModel& setEnableRoomHit(bool enable)
        {
            m_enableRoomHit = enable;
            return *this;
        }

        MapColliderModel& setIsThrough(bool isThrough)
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
        const s3d::Array<Ref<TerrainModel>>& getHitTerrains() const;

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
    struct ComponentTree<MapColliderModel>
    {
        using Base = MultiComponents<
            IPrePhysicsModel,
            IPhysicsModel,
            ILastPhysicsModel
        >;
    };
}