#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/types/ColDirection.hpp>

namespace abyss::Actor::Land
{
    class LandProxy :
        public IComponent
    {
    private:
        ColDirection m_col;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_size;
    public:
        LandProxy(ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size);

        const s3d::Vec2& getPos() const;
        const s3d::Vec2& getSize() const;
        s3d::RectF region() const;

        ColDirection getCol() const;
    };
}
