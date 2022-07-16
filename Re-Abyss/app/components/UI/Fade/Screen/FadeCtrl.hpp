#pragma once
#include <memory>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::Fade::Screen
{
    class ScreenVM;

    class FadeCtrl :
        public IComponent,
        public IDraw
    {
    public:
        FadeCtrl(UIObj* pUi);
        ~FadeCtrl();

        FadeCtrl& setFadeTime(double fadeTimeSec);
        FadeCtrl& setIsFadeOut(bool isFadeOut);
        FadeCtrl& setIsFadeIn(bool isFadeIn);

        void destroy();
        void onDraw() const override;
    private:
        UIObj* m_pUi;
        double m_fadeTimeSec = 0;
        bool m_isFadeOut = true;

        std::unique_ptr<ScreenVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Fade::Screen::FadeCtrl>
    {
        using Base = MultiComponents<UI::IDraw>;
    };
}
