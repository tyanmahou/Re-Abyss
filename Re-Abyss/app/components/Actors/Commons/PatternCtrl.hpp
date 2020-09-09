#pragma once
#include <functional>
#include <Siv3D/Duration.hpp>
#include <Siv3D/Uncopyable.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/LoopQueue/LoopQueue.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
namespace abyss::Actor
{
    class PatternCtrl : 
        public IComponent,
        private s3d::Uncopyable
    {
        IActor* m_pActor = nullptr;
        LoopQueue<std::function<void()>> m_events;
        TimerEx m_sleep;
        s3d::Array<size_t> m_eventStepNo;
        s3d::Array<size_t> m_toStepCount;
    public:
        PatternCtrl();
        PatternCtrl(IActor* pActor);

        void setup() override;
        bool update();
        PatternCtrl& add(const std::function<void()>& event);

        PatternCtrl& sleep(double time);
        PatternCtrl& sleep(const s3d::Duration& time);

        PatternCtrl& toStep(size_t step);
        PatternCtrl& toStep(size_t step, size_t count);

        PatternCtrl& clear();
    };
}