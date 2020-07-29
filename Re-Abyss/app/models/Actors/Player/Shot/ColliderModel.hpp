#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Player::Shot
{
    class PlayerShotModel;

    /// <summary>
    /// 当たり判定
    /// </summary>
    class ColliderModel :
        public IComponent,
        public IColliderModel
    {
    private:
        Ref<BodyModel> m_body;
        Ref<PlayerShotModel> m_shot;
    public:
        using IColliderModel::IColliderModel;

        void setup() override;

        s3d::Circle getColliderCircle() const;
        CShape getCollider() const override
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Player::Shot::ColliderModel>
    {
        using Base = IColliderModel;
    };
}