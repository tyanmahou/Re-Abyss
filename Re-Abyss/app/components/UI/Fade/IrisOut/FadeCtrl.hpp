#pragma once
#include <memory>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::Fade::IrisOut
{
    class IrisOutVM;

    class FadeCtrl :
        public IComponent,
        public IDraw
    {
    public:
        FadeCtrl(UIObj* pUi);
        ~FadeCtrl();

        FadeCtrl& setPos(const s3d::Vec2& pos);
        FadeCtrl& setFadeTime(double fadeTimeSec);
        FadeCtrl& setIsFadeOut(bool isFadeOut);
        FadeCtrl& setIsFadeIn(bool isFadeIn);
        FadeCtrl& setColor(const s3d::ColorF& color);

        void destroy();
        void onDraw() const override;
    private:
        UIObj* m_pUi;
        s3d::Vec2 m_pos;
        std::unique_ptr<IrisOutVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::Fade::IrisOut::FadeCtrl>
    {
        using Base = MultiComponents<UI::IDraw>;
    };
}
