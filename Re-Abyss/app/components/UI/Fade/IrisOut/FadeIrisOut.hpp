#pragma once
#include <memory>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::ui::Fade::IrisOut
{
    class IrisOutVM;

    class FadeIrisOut :
        public IComponent,
        public IDraw
    {
    public:
        FadeIrisOut(IUserInterface* pUi);

        FadeIrisOut& setPos(const s3d::Vec2& pos);
        FadeIrisOut& setFadeTime(double fadeTimeSec);
        FadeIrisOut& setIsFadeOut(bool isFadeOut);
        FadeIrisOut& setIsFadeIn(bool isFadeIn);

        void destroy();
        void onDraw() const override;
    private:
        IUserInterface* m_pUi;

        s3d::Vec2 m_pos;
        double m_fadeTimeSec = 0;
        bool m_isFadeOut = true;

        std::unique_ptr<IrisOutVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<ui::Fade::IrisOut::FadeIrisOut>
    {
        using Base = MultiComponents<ui::IDraw>;
    };
}