#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::Fade::IrisOut
{
    class FadeCtrl;
}

namespace abyss::Event
{
    class FadeIrisOut : public IComponent
    {
    public:
        FadeIrisOut(EventObj* pEvent, bool createOnStart = true);

        void onStart() override;
        void onEnd() override;

        void create();
        void destroy();

        FadeIrisOut& setIsFadeIn(bool fadeIn);
        FadeIrisOut& setPos(const s3d::Vec2& pos);
        FadeIrisOut& setFadeTime(double time);
    private:
        EventObj* m_pEvent;
        Ref<UI::Fade::IrisOut::FadeCtrl> m_fadeUI;
        bool m_createOnStart;
    };
}