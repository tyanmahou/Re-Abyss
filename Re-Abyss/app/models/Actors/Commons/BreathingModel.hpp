#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/Components.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
    class BreathingModel : 
        public IComponent,
        public ILastUpdateModel
    {
    public:
        BreathingModel(IActor* pActor);

        void setup() override;
        void onLastUpdate() override;

        void setOffset(const Vec2& offset)
        {
            m_offset = offset;
        }
    private:
        IActor* m_pActor;
        IntervalTimer m_timer;
        s3d::Vec2 m_offset;
        double m_timeOffsetSec = 0;
        Ref<BodyModel> m_body;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<BreathingModel>
    {
        using Base = ILastUpdateModel;
    };
}