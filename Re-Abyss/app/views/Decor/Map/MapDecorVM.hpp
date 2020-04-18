#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Decor/base/IDecorVM.hpp>
#include <abyss/models/Decor/Map/MapDecorModel.hpp>

namespace abyss
{
    class MapDecorVM : public IDecorVM
    {
        DecorGraphicsManager* m_manager;
        MapDecorModel m_model;
    public:
        MapDecorVM(
            DecorGraphicsManager* manager,
            const MapDecorModel& model
        );
        void draw(const s3d::RectF& screen) const override;
    };
}