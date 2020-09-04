#pragma once
#include <functional>
#include <Siv3D/Duration.hpp>
#include <Siv3D/Uncopyable.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/LoopQueue/LoopQueue.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
namespace abyss
{
    class PatternModel : 
        public IComponent,
        private s3d::Uncopyable
    {
        IActor* m_pActor = nullptr;
        LoopQueue<std::function<void()>> m_events;
        TimerEx m_sleep;
        s3d::Array<size_t> m_eventStepNo;
        s3d::Array<size_t> m_toStepCount;
    public:
        PatternModel();
        PatternModel(IActor* pActor);

        void setup() override;
        bool update();
        PatternModel& add(const std::function<void()>& event);

        PatternModel& sleep(double time);
        PatternModel& sleep(const s3d::Duration& time);

        PatternModel& toStep(size_t step);
        PatternModel& toStep(size_t step, size_t count);

        PatternModel& clear();
    };
}