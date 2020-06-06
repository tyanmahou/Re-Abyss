#include "WaterSarfaceView.hpp"
#include <Siv3D.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>


namespace abyss
{
    WaterSarfaceView::WaterSarfaceView():
		m_texture(ResourceManager::Main()->loadTexture(U"bgs/surface.png"))
    {}

	void WaterSarfaceView::drawBack(const CameraView& camera) const
	{
		const auto& screen = Constants::GameScreenSize;
		const auto& pos = camera.getCameraPos();
		double u = (pos.x) / screen.x / 8.0;
		double v = (pos.y) / screen.y / 8.0;
		auto time = Scene::Time() / 60.0;
		{
			ScopedRenderStates2D state(BlendState::Subtractive, SamplerState::RepeatNearest);
			m_texture.uv(u + time, v + time, 1, 1).scaled(2.0).drawAt(pos);
		}
		{
			ScopedRenderStates2D state(BlendState::Additive, SamplerState::RepeatNearest);
			m_texture.uv(u + time / 2.0 + 0.5, v + time + 0.5, 1, 1).scaled(2.0).drawAt(pos);
		}
	}
	void WaterSarfaceView::drawFront(const CameraView& camera) const
	{
		const auto& screen = Constants::GameScreenSize;
		const auto& pos = camera.getCameraPos();
		double u = (pos.x) / screen.x / 2.0;
		double v = (pos.y) / screen.y / 2.0;
		auto time = Scene::Time() / 30.0;
		{
			ScopedRenderStates2D state(BlendState::Subtractive, SamplerState::RepeatNearest);
			m_texture.uv(u - time, v + time, 1, 1).scaled(1.5).drawAt(pos);
		}
		{
			ScopedRenderStates2D state(BlendState::Additive, SamplerState::RepeatNearest);
			m_texture.uv(u - time / 2.0 + 0.5, v + time + 0.5, 1, 1).scaled(1.5).drawAt(pos);
		}
	}
}
