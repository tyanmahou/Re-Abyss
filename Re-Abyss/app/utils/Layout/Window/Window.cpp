#include <abyss/utils/Layout/Window/Window.hpp>

#include <abyss/utils/Layout/Window/detail/Component.hpp>
#include <abyss/utils/Layout/Window/detail/Constants.hpp>
#include <abyss/utils/Layout/Window/detail/GrabCtrl.hpp>
#include <abyss/utils/Layout/Window/detail/ScrollCtrl.hpp>
#include <abyss/utils/Layout/Window/detail/WindowParam.hpp>
#include <Siv3D.hpp>

namespace abyss::Layout::Window
{
	using namespace detail;

    WindowContext::WindowContext() :
        WindowContext({ 300, 300 })
    {}
    WindowContext::WindowContext(const s3d::Vec2& _size) :
        WindowContext({ 0, 0 }, _size, _size)
    {}
    WindowContext::WindowContext(const s3d::Vec2& _pos, const s3d::Vec2& _size) :
        WindowContext(_pos, _size, _size)
    {}
    WindowContext::WindowContext(const s3d::Vec2& _pos, const s3d::Vec2& _size, const s3d::Vec2& _sceneSize) :
        pos(_pos),
        size(_size),
        sceneSize(_sceneSize),
        backGroundColor(Palette::White),
        frameColor(Color(240)),
        scrollBarColor(Color(240)),
        scrollGripColor(Color(133))
    {}
    WindowContext& WindowContext::setBackGroundColor(const s3d::Optional<s3d::ColorF>& color)
    {
        backGroundColor = color;
        return *this;
    }
    WindowContext& WindowContext::setFrameColor(const s3d::Optional<s3d::ColorF>& color)
    {
        frameColor = color;
        return *this;
    }
    WindowContext& WindowContext::setScrollBarColor(const s3d::ColorF& color)
    {
        scrollBarColor = color;
        return *this;
    }
    WindowContext& WindowContext::setScrollGripColor(const s3d::ColorF& color)
    {
        scrollGripColor = color;
        return *this;
    }

    class Window::Handle : public WindowParam
    {
    public:
        Handle(const WindowContext& context) :
            m_comp(*this)
        {
            this->pos = context.pos;
            this->setSize(context.size);
            this->sceneSize = context.sceneSize;
            this->scenePos = {};

            this->backGroundColor = context.backGroundColor;
            this->frameColor = context.frameColor;
            this->scrollBarColor = context.scrollBarColor;
            this->scrollGripColor = context.scrollGripColor;
        }
        void setSize(const s3d::Vec2& _size)
        {
            if (this->sceneSize.x > _size.x) {
                this->size.x = s3d::Max(_size.x, Constants::WinMinSize.x);
            } else {
                this->size.x = _size.x;
            }
            if (this->sceneSize.y > _size.y) {
                this->size.y = s3d::Max(_size.y, Constants::WinMinSize.x);
            } else {
                this->size.y = _size.y;
            }
        }
        void setScenePos(const s3d::Vec2& _pos)
        {
            this->scenePos.x = s3d::Clamp(_pos.x, 0.0, Max(sceneSize.x - size.x, 0.0));
            this->scenePos.y = s3d::Clamp(_pos.y, 0.0, Max(sceneSize.y - size.y, 0.0));
        }
        void update()
        {
            m_comp.grabCtrl().update();

            // Clamp
            this->setScenePos(this->scenePos);
        }
        s3d::Rect region() const
        {
            return this->regionF().asRect();
        }
        s3d::RectF regionF() const
        {
            return WindowParam::region;
        }
        s3d::ScopedViewport2D startViewport() const
        {
            return s3d::ScopedViewport2D{ this->region() };
        }
        s3d::Transformer2D transformer() const
        {
            return { Mat3x2::Translate(-scenePos), Mat3x2::Translate(pos - scenePos) };
        }
        s3d::RectF draw(std::function<void(const s3d::RectF&)> scene)
        {
            this->update();

            auto region = this->regionF();
            if (backGroundColor) {
                region.draw(*backGroundColor);
            }
            {
                auto t2d = this->transformer();
                auto viewport = this->startViewport();
                scene(region);
            }
            m_comp.scrollCtrl().draw(scrollBarColor, scrollGripColor);

            if (frameColor) {
                region.drawFrame(0, 1, *frameColor);
            }
            return region;
        }
    private:
        detail::Component m_comp;
    };

    Window::Window() :
        Window({ 100, 100 })
    {}
    Window::Window(const s3d::Vec2& size) :
        Window({ 0, 0 }, size)
    {}
    Window::Window(const s3d::Vec2& pos, const s3d::Vec2& size) :
        Window(pos, size, size)
    {}
    Window::Window(
        const s3d::Vec2& pos,
        const s3d::Vec2& size,
        const s3d::Vec2& sceneSize
    ) :
        Window(WindowContext{ pos, size, sceneSize })
    {}
    Window::Window(const WindowContext& context) :
        m_pHandle(std::make_shared<Handle>(context))
    {}
    Window& Window::setPos(const s3d::Vec2& pos)
    {
        m_pHandle->pos = pos;
        return *this;
    }
    Window& Window::setSize(const s3d::Vec2& size)
    {
        m_pHandle->setSize(size);
        return *this;
    }
    Window& Window::setScenePos(const s3d::Vec2& scenePos)
    {
        m_pHandle->setScenePos(scenePos);
        return *this;
    }
    Window& Window::setSceneSize(const s3d::Vec2& sceneSize)
    {
        m_pHandle->sceneSize = sceneSize;
        return *this;
    }
    Window& Window::setBackGroundColor(const s3d::Optional<s3d::ColorF>& color)
    {
        m_pHandle->backGroundColor = color;
        return *this;
    }
    Window& Window::setFrameColor(const s3d::Optional<s3d::ColorF>& color)
    {
        m_pHandle->frameColor = color;
        return *this;
    }
    Window& Window::setScrollBarColor(const s3d::ColorF& color)
    {
        m_pHandle->scrollBarColor = color;
        return *this;
    }
    Window& Window::setScrollGripColor(const s3d::ColorF& color)
    {
        m_pHandle->scrollGripColor = color;
        return *this;
    }
    s3d::RectF Window::draw(std::function<void(const s3d::RectF&)> scene) const
    {
        return m_pHandle->draw(std::move(scene));
    }
}
