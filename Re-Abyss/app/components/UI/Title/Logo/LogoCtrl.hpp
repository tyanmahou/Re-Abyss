#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>


namespace abyss::UI::Title::Logo
{
    class LogoCtrl :
        public IComponent,
        public IUpdate
    {
        enum class Phase
        {
            Start,
            Step1,
            Step2,
            Step3,
            Step4,
            Step5,
            End,
        };
        struct ViewParam
        {
            s3d::Vec2 pos;
            double alpha;
        };
    public:
        LogoCtrl(UIObj* pUi);

        void onUpdate() override;

        bool isEnd() const;

        std::pair<s3d::Optional<ViewParam>, s3d::Optional<ViewParam>> getViewParams() const;
    private:
        double time0_1() const;
    private:
        UIObj* m_pUi;

        s3d::Timer m_timer;
        Phase m_phase = Phase::Start;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Title::Logo::LogoCtrl>
    {
        using Base = MultiComponents<UI::IUpdate>;
    };
}