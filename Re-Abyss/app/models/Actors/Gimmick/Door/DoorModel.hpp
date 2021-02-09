#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/entities/Actors/Gimmick/DoorEntity.hpp>

namespace abyss::Actor::Gimmick::Door
{
    class DoorModel
    {
        s3d::int32 m_startId;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_targetPos;
        Forward m_targetForward;
        s3d::Vec2 m_size;
        DoorKind m_kind;
        bool m_isSave = true;
    public:
        DoorModel() = default;
        DoorModel(
            s3d::int32 startId,
            const s3d::Vec2& pos, 
            const s3d::Vec2& targetPos, 
            Forward targetForward,
            const s3d::Vec2& size,
            DoorKind kind,
            bool isSave
        );

        s3d::int32 getStartId()const
        {
            return m_startId;
        }
        const s3d::Vec2& getPos()const
        {
            return m_pos;
        }
        const s3d::Vec2& getTargetPos() const
        {
            return m_targetPos;
        }
        Forward  getTargetForward() const
        {
            return m_targetForward;
        }
        const s3d::Vec2& getSize() const
        {
            return m_size;
        }
        DoorKind getKind() const
        {
            return m_kind;
        }
        bool isSave() const
        {
            return m_isSave;
        }
        s3d::Vec2 fixedVisiterPos(const s3d::Vec2& visitSize = { 22,80 }) const;
    };
}