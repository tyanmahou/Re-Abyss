#pragma once
#include <memory>
#include <Siv3D/Rect.hpp>
#include <Siv3D/RectF.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Layout::Window
{
    struct WindowContext
    {
    public:
        WindowContext();
        WindowContext(const s3d::Vec2& _size);
        WindowContext(const s3d::Vec2& _pos, const s3d::Vec2& _size);
        WindowContext(const s3d::Vec2& _pos, const s3d::Vec2& _size, const s3d::Vec2& _sceneSize);

        WindowContext& setBackGroundColor(const s3d::Optional<s3d::ColorF>& color);
        WindowContext& setFrameColor(const s3d::Optional<s3d::ColorF>& color);
        WindowContext& setScrollBarColor(const s3d::ColorF& color);
        WindowContext& setScrollGripColor(const s3d::ColorF& color);

        WindowContext& setCanResize(bool _canResize)
        {
            this->canResize = _canResize;
            return *this;
        }
        WindowContext& setIsResizeClampSceneSize(bool _isResizeClampSceneSize)
        {
            this->isResizeClampSceneSize = _isResizeClampSceneSize;
            return *this;
        }
        WindowContext& setCanMove(bool _canMove)
        {
            this->canMove = _canMove;
            return *this;
        }
        WindowContext& setCanScroll(bool _canScroll)
        {
            this->canScroll = _canScroll;
            return *this;
        }
    public:
        s3d::Vec2 pos;
        s3d::Vec2 size;
        s3d::Vec2 sceneSize;

        s3d::Optional<ColorF> backGroundColor;
        s3d::Optional<ColorF> frameColor;
        s3d::ColorF scrollBarColor;
        s3d::ColorF scrollGripColor;

        bool canResize = true;
        bool isResizeClampSceneSize = false;
        bool canMove = true;
        bool canScroll = true;
    };

    /// <summary>
    /// 仮想ウィンドウ
    /// </summary>
    class Window
    {
        class Handle;
    public:
        Window();
        Window(const s3d::Vec2& size);
        Window(const s3d::Vec2& pos, const s3d::Vec2& size);
        Window(const s3d::Vec2& pos, const s3d::Vec2& size, const s3d::Vec2& sceneSize);

        Window(const WindowContext& context);

        /// <summary>
        /// ウィンドウの座標を設定
        /// </summary>
        Window& setPos(const s3d::Vec2& pos);

        /// <summary>
        /// ウィンドウのサイズを設定
        /// </summary>
        Window& setSize(const s3d::Vec2& size);

        /// <summary>
        /// シーンの座標を設定
        /// </summary>
        Window& setScenePos(const s3d::Vec2& scenePos);

        /// <summary>
        /// シーンの座標を一番下にする
        /// </summary>
        Window& setScenePosToBottom();

        /// <summary>
        /// スクロールが一番下にあるか
        /// </summary>
        bool isScrollBottom() const;

        /// <summary>
        /// シーンのサイズを設定する
        /// </summary>
        Window& setSceneSize(const s3d::Vec2& sceneSize);

        Window& setBackGroundColor(const s3d::Optional<s3d::ColorF>& color);
        Window& setFrameColor(const s3d::Optional<s3d::ColorF>& color);
        Window& setScrollBarColor(const s3d::ColorF& color);
        Window& setScrollGripColor(const s3d::ColorF& color);

        /// <summary>
        /// 描画
        /// </summary>
        s3d::RectF draw(std::function<void(const s3d::RectF&)> scene) const;
    private:
        std::shared_ptr<Handle> m_pHandle;
    };
}
