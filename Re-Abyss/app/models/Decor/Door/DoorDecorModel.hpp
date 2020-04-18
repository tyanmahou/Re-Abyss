#pragma once
#include <abyss/models/Decor/base/IDecorModel.hpp>
#include <abyss/entities/Actors/Gimmick/DoorEntity.hpp>

namespace abyss
{
    class DoorDecorModel : public IDecorModel
    {
        s3d::Vec2 m_pos;
        s3d::Vec2 m_size;
        DoorKind m_kind;
    public:
        DoorDecorModel(const s3d::Vec2& pos, const s3d::Vec2& size, DoorKind kind);
        const s3d::Vec2& getPos()const { return m_pos; }
        const s3d::Vec2& getSize()const { return m_size; }
        DoorKind getKind()const { return m_kind; }
        s3d::RectF region() const;
        bool isInScreen(const s3d::RectF& screen) const override;
    };
}