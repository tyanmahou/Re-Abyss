#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IPhysicsModel.hpp>

namespace abyss
{
    class MapColliderModel:
        public IComponent,
        public IPhysicsModel
    {
    private:
        Ref<BodyModel> m_body;
        Ref<MapColResultModel> m_result;
    public:

        using IPhysicsModel::IPhysicsModel;

        void setup() override;
        s3d::RectF getCollider() const override;

        void onCollision(const Ref<TerrainModel>& terrain) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<MapColliderModel>
    {
        using Base = IPhysicsModel;
    };
}