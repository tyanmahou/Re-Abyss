#pragma once
#include <memory>
#include <Siv3D/Rect.hpp>
#include <Siv3D/RectF.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Layout::Window
{
    /// <summary>
    /// 仮想ウィンドウ
    /// </summary>
    class Window
    {
        class Handle;
    public:
        Window();
        Window(double w, double h);
        Window(const s3d::Vec2& size);
        Window(const s3d::Vec2& pos, const s3d::Vec2& size);
        Window(const s3d::Vec2& pos, const s3d::Vec2& size, const s3d::Vec2& sceneSize);

        Window& setBackGround(const s3d::Optional<s3d::ColorF>& color);
        Window& setFrameColor(const s3d::Optional<s3d::ColorF>& color);

        s3d::RectF draw(std::function<void(const s3d::RectF&)> scene) const;
    private:
        std::shared_ptr<Handle> m_pHandle;
    };
}
