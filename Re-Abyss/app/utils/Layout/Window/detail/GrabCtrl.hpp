#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/CursorStyle.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Layout::Window::detail
{
    class Component;

    enum class GrabState
    {
        None,
        Top, Bottom, Left, Right,
        Tl, Tr, Bl, Br,
        Move,
        ScrollV, ScrollH,
        ScrollUp, ScrollDown, ScrollLeft, ScrollRight,
        ScrollVTo, ScrollHTo,
    };

    class IGrabHandler
    {
    public:
        virtual ~IGrabHandler() = default;

        /// <summary>
        /// 掴めるかどうか
        /// </summary>
        /// <returns>掴めるなら true で以降の他のハンドラはスルーされる</returns>
        virtual bool onGrabPromise() = 0;

        /// <summary>
        /// 掴みチェックの前の更新処理
        /// 全てのハンドラに呼ばれる
        /// </summary>
        /// <param name="isPromised"></param>
        virtual void onPreGrabCheck(bool isPromised) = 0;

        /// <summary>
        /// 掴みチェック
        /// </summary>
        /// <returns></returns>
        virtual s3d::Optional<GrabState> onGrabCheck() = 0;

        /// <summary>
        /// 捕まれた
        /// </summary>
        /// <param name="state"></param>
        virtual void onGrab(GrabState state) = 0;

        /// <summary>
        /// 捕まれ中
        /// </summary>
        /// <param name="state"></param>
        virtual void onGrabUpdate(GrabState state) = 0;

        /// <summary>
        /// 離された
        /// </summary>
        virtual void onGrabRelease() = 0;
    };

    /// <summary>
    /// 掴み制御
    /// </summary>
    class GrabCtrl
    {
    public:
        GrabCtrl(Component* pComp);
        bool isGrab() const { return m_isGrab; }

        const s3d::Vec2& grabCursorPos() const
        {
            return m_grabCursorPos;
        }
        const s3d::Vec2& grabPos() const
        {
            return m_grabPos;
        }
        const s3d::Vec2& grabSize() const
        {
            return m_grabSize;
        }
        const s3d::Vec2& grabScenePos() const
        {
            return m_grabScenePos;
        }
        void update();

        void registHandler(IGrabHandler* handler);
    private:
        Component* m_pComp;

        bool m_isGrab = false;
        GrabState m_grabState{};

        s3d::Vec2 m_grabCursorPos{};
        s3d::Vec2 m_grabPos{};
        s3d::Vec2 m_grabSize{};
        s3d::Vec2 m_grabScenePos{};

        s3d::Array<IGrabHandler*> m_handlers;
        IGrabHandler* m_promosedHandler = nullptr;
    };
}
