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
    public:
        s3d::Vec2 pos;
        s3d::Vec2 size;
        s3d::Vec2 sceneSize;

        s3d::Optional<ColorF> backGroundColor;
        s3d::Optional<ColorF> frameColor;
        s3d::ColorF scrollBarColor;
        s3d::ColorF scrollGripColor;
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

        Window& setPos(const s3d::Vec2& pos);
        Window& setSize(const s3d::Vec2& size);
        Window& setScenePos(const s3d::Vec2& scenePos);
        Window& setSceneSize(const s3d::Vec2& sceneSize);

        Window& setBackGroundColor(const s3d::Optional<s3d::ColorF>& color);
        Window& setFrameColor(const s3d::Optional<s3d::ColorF>& color);

        s3d::RectF draw(std::function<void(const s3d::RectF&)> scene) const;
    private:
        std::shared_ptr<Handle> m_pHandle;
    };
}
