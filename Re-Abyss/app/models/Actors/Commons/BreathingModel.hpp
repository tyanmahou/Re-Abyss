#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/Components.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
    class BreakthingModel : 
        public IComponent,
        public ILastUpdateModel
    {
    public:
        BreakthingModel(IActor* pActor);

        void setup() override;
        void onLastUpdate(double dt) override;

        void setOffset(const Vec2& offset)
        {
            m_offset = offset;
        }
    private:
        IActor* m_pActor;
        IntervalTimer m_timer;
        s3d::Vec2 m_offset;

        Ref<BodyModel> m_body;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<BreakthingModel>
    {
        using Base = ILastUpdateModel;
    };
}