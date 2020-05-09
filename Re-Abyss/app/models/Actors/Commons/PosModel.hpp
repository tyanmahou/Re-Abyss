#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <Siv3D/Vector2D.hpp>
namespace abyss
{
    class PosModel : public IComponent
    {
        s3d::Vec2 m_prevPos;
        s3d::Vec2 m_pos;
    public:
        PosModel() = default;
        PosModel(s3d::Vec2& pos);

        PosModel& initPos(const s3d::Vec2& pos);
        PosModel& setPos(const s3d::Vec2& pos);
        PosModel& setPosX(double x);
        PosModel& setPosY(double y);
        PosModel& addPos(const s3d::Vec2& deltaPos);
        PosModel& addPosX(double deltaX);
        PosModel& addPosY(double deltaY);

        const s3d::Vec2& getPos() const;
        const s3d::Vec2& getPrevPos() const;
    };
}