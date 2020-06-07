#include "WaterSarfaceView.hpp"
#include <Siv3D.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace
{
	using namespace abyss;

	void Draw(
		const CameraView& camera, 
		const s3d::Texture& texture,
		double uvRate,
		const Vec2& timeRate,
		double scale,
		double time
	) {
		const auto& pos = camera.getCameraPos();
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
namespace abyss
{
    WaterSarfaceView::WaterSarfaceView():
		m_texture(ResourceManager::Main()->loadTexture(U"bgs/surface.png"))
    {}

	void WaterSarfaceView::drawBack(const CameraView& camera) const
	{
		auto time = Scene::Time() / 60.0;
		::Draw(camera, m_texture, 8.0, Vec2{ 1.0, 1.0 }, 2.0, time);
	}
	void WaterSarfaceView::drawFront(const CameraView& camera) const
	{
		auto time = Scene::Time() / 30.0;
		::Draw(camera, m_texture, 2.0, Vec2{ -1.0, 1.0 }, 1.5, time);
	}
}
