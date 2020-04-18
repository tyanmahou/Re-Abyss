#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Decor/base/IDecorVM.hpp>
#include <abyss/models/Decor/Common/CommonDecorModel.hpp>

namespace abyss
{
    class CommonDecorVM : public IDecorVM
    {
        DecorGraphicsManager* m_manager;
        CommonDecorModel m_model;
    public:
        CommonDecorVM(
            DecorGraphicsManager* manager,
            const CommonDecorModel& model
        );

        void draw(const s3d::RectF& screen) const override;
    };
}