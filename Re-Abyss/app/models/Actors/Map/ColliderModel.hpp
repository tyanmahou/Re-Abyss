#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IColliderModel.hpp>

namespace abyss::Map
{
    class ColliderModel : 
        public IComponent,
        public IColliderModel
    {
    private:
        s3d::Vec2 m_pos;
        s3d::Vec2 m_size;
    public:
        ColliderModel(IActor* pActor, const s3d::Vec2& pos, const s3d::Vec2& size);

        const s3d::Vec2& getPos() const;
        const s3d::Vec2& getSize() const;
        s3d::RectF region() const;
        CShape getCollider() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Map::ColliderModel>
    {
        using Base = IColliderModel;
    };
}