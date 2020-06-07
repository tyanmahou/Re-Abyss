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
	BackGroundView::BackGroundView()
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
			m_sky.draw(camera);
			{
				ScopedRenderStates2D state(YClamp);
				for (const auto& bg : m_bgs) {
					bg.draw(pos);
				}
			}
		});
	}

}
