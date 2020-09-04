#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss::Actor::Map
{
    class MapParam;

    class MapActor :public IActor
    {
    protected:
        ColDirection m_col;
        Ref<MapParam> m_mapParam;
    public:
        MapActor(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

        const s3d::Vec2& getPos() const;
        const s3d::Vec2& getSize() const;
        ColDirection getCol() const;
        s3d::RectF region() const;
        CShape getCollider() const;

        bool accept(const ActVisitor& visitor) override;

        MapColInfo getMapColInfo() const;
    };

}