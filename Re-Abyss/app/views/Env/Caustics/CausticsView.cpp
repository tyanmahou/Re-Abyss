#include <abyss/views/Env/Caustics/CausticsView.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
	using namespace abyss;

	void Draw(
		const Vec2& pos, 
		const s3d::Texture& texture,
		double uvRate,
		const Vec2& timeRate,
		double scale,
		double time
	) {
		double u = pos.x / Constants::GameScreenSize.x / uvRate;
		double v = pos.y / Constants::GameScreenSize.y / uvRate;
		{
			ScopedRenderStates2D state(BlendState::Subtractive, SamplerState::RepeatNearest);
			texture.uv(u + time * timeRate.x, v + time * timeRate.y, 1, 1).scaled(scale).drawAt(pos);
		}
		{
			ScopedRenderStates2D state(BlendState::Additive, SamplerState::RepeatNearest);
			texture.uv(u + time * timeRate.x / 2.0 + 0.5, v + time * timeRate.y + 0.5, 1, 1).scaled(scale).drawAt(pos);
		}
	}
}
namespace abyss::Env
{
	CausticsView::CausticsView():
		m_texture(Resource::Assets::Main()->load(U"Env/caustics.png")),
		m_time(0)
    {}

	CausticsView& CausticsView::setTime(double time)
	{
		m_time = time;
		return *this;
	}

	void CausticsView::drawBack(const Vec2& pos) const
	{
		auto time = m_time / 60.0;
		::Draw(pos, m_texture, 8.0, Vec2{ 1.0, 1.0 }, 2.0, time);
	}
	void CausticsView::drawFront(const Vec2& pos) const
	{
		auto time = m_time / 30.0;
		::Draw(pos, m_texture, 2.0, Vec2{ -1.0, 1.0 }, 1.5, time);
	}
}
