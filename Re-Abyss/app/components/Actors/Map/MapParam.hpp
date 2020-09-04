#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>

namespace abyss::Actor::Map
{
    class MapParam :
        public IComponent
    {
    private:
        s3d::Vec2 m_pos;
        s3d::Vec2 m_size;
    public:
        MapParam(const s3d::Vec2& pos, const s3d::Vec2& size);

        const s3d::Vec2& getPos() const;
        const s3d::Vec2& getSize() const;
        s3d::RectF region() const;
    };
}