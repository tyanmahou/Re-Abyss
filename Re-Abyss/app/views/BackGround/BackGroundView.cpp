#include "BackGroundView.hpp"
#include <Siv3D.hpp>
#include <abyss/views/Camera/CameraView.hpp>

namespace
{
	static const SamplerState YClamp(
		TextureAddressMode::Repeat,
		TextureAddressMode::Clamp,
		TextureAddressMode::Repeat,
		TextureFilter::Nearest,
		TextureFilter::Nearest,
		TextureFilter::Nearest
	);
}
namespace abyss
{
	BackGroundView::BackGroundView():
		m_skyTexture(U"work/stage0/sky.png")
	{}
	void BackGroundView::addBackGround(const BackGroundVM & bg)
	{
		m_bgs.push_back(bg);
	}

    void BackGroundView::draw(const CameraView& camera) const
    {
		m_waveShader.apply(camera, [&]() {
			auto pos = camera.getCameraPos();
			camera.screenRegion().draw(Color(14, 56, 72));
			{
				ScopedRenderStates2D blend(BlendState::Additive, SamplerState::MirrorNearest);
				auto shader = m_skyShader.start();
				auto tl = camera.screenRegion().tl();
				auto offset = Vec2{ 0, - tl.y / 20.0 };
				m_skyTexture.draw(tl + offset, Arg::top(ColorF(1,1)), Arg::bottom(ColorF(1, 0)));
			}
			{
				ScopedRenderStates2D state(YClamp);
				for (const auto& bg : m_bgs) {
					bg.draw(pos);
				}
			}
		});
	}

}
