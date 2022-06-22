#pragma once
#include <memory>
#include <abyss/utils/Layout/Window/detail/GrabCtrl.hpp>

namespace abyss::Layout::Window::detail
{
    class Component;

    /// <summary>
    /// シーンスクロール制御
    /// </summary>
    class ScrollCtrl : public IGrabHandler
    {
    public:
        class View;
    public:
        ScrollCtrl(Component* pComp);

        void draw(const s3d::ColorF& barColor, const s3d::ColorF& gripColor) const;
    public:
        bool onGrabPromise() override;
        void onPreGrabCheck(bool isPromised) override;
        s3d::Optional<GrabState> onGrabCheck() override;

        void onGrab(GrabState state);
        void onGrabUpdate(GrabState state);
        void onGrabRelease();
    private:
        GrabCtrl& grab() const;
    private:
        Component* m_pComp;
        std::unique_ptr<View> m_view;
        double m_waitTimer = 0;
    };
}
