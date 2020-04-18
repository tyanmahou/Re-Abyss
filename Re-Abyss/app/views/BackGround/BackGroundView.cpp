#include "BackGroundView.hpp"
#include <Siv3D.hpp>
#include <abyss/views/Camera/CameraView.hpp>
namespace
{
	static const SamplerState YClamp(
		TextureAddressMode::Repeat,
		TextureAddressMode::Clamp,
		TextureAddressMode::Repeat
	);
}
namespace abyss
{
	void BackGroundView::addBackGround(const BackGroundVM & bg)
	{
		m_bgs.push_back(bg);
	}

    void BackGroundView::draw(const CameraView& camera) const
    {
		m_waveShader.apply(camera, [&]() {
			ScopedRenderStates2D state(YClamp);
			for (const auto& bg : m_bgs) {
				bg.draw(camera.getCameraPos());
			}
		});
	}

}
