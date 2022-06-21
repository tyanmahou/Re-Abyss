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

	class Window::Handle : public WindowParam
	{
	public:
		Handle(const s3d::Vec2& _pos, const s3d::Vec2& _size, const s3d::Vec2& _sceneSize) :
			m_comp(*this)
		{
			this->pos = _pos;
			this->size.x = s3d::Max(_size.x, Constants::WinMinSize.x);
			this->size.y = s3d::Max(_size.y, Constants::WinMinSize.x);
			this->sceneSize = _sceneSize;
			this->scenePos = {};
		}
		void setBackground(const s3d::Optional<s3d::ColorF>& color)
		{
			m_backGroundColor = color;
		}
		void setFrameColor(const s3d::Optional<s3d::ColorF>& color)
		{
			m_frameColor = color;
		}
		void update()
		{
			m_comp.grabCtrl().update();

			scenePos.x = s3d::Clamp(scenePos.x, 0.0, Max(sceneSize.x - size.x, 0.0));
			scenePos.y = s3d::Clamp(scenePos.y, 0.0, Max(sceneSize.y - size.y, 0.0));
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
			if (m_backGroundColor) {
				region.draw(*m_backGroundColor);
			}
			{
				auto t2d = this->transformer();
				auto viewport = this->startViewport();
				scene(region);
			}
			m_comp.scrollCtrl().draw();

			if (m_frameColor) {
				region.drawFrame(0, 1, *m_frameColor);
			}
			return region;
		}
	private:
		s3d::Optional<ColorF> m_backGroundColor{};
		s3d::Optional<ColorF> m_frameColor{};
		detail::Component m_comp;
	};

	Window::Window() :
		Window({ 100, 100 })
	{}
	Window::Window(double w, double h) :
		Window(Vec2{ w, h })
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
		m_pHandle(std::make_shared<Handle>(pos, size, sceneSize))
	{}
	Window& Window::setBackGround(const s3d::Optional<s3d::ColorF>& color)
	{
		m_pHandle->setBackground(color);
		return *this;
	}
	Window& Window::setFrameColor(const s3d::Optional<s3d::ColorF>& color)
	{
		m_pHandle->setFrameColor(color);
		return *this;
	}
	s3d::RectF Window::draw(std::function<void(const s3d::RectF&)> scene) const
	{
		return m_pHandle->draw(std::move(scene));
	}
}
