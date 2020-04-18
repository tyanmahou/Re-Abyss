#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Decor/base/IDecorVM.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/models/Decor/Door/DoorDecorModel.hpp>
namespace abyss
{
    class DoorDecorVM : public IDecorVM
    {
        TexturePacker m_texture;
        DoorDecorModel m_model;
        void drawCommon() const;
        void drawBoss() const;
    public:
        DoorDecorVM(const DoorDecorModel& model);
        void draw(const s3d::RectF& screen) const override;
    };
}