#include "BackGroundView.hpp"
#include <application/common/Constants.hpp>
#include <Siv3D.hpp>
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
	void BackGroundVM::draw(const s3d::Vec2& pos) const
	{
		const auto& screen = Constants::GameScreenSize;

		double u = loop.x ? (pos.x - screen.x / 2 - offset.x) / screen.x / rate.x : 0;
		double v = loop.y ? (pos.y - screen.y / 2 - offset.y) / screen.y / rate.y : 0;
		double x = loop.x ? pos.x : offset.x + texture.size().x / 2;
		double y = loop.y ? pos.y : offset.y + texture.size().y / 2;
		texture.uv(u, v, 1, 1).drawAt({ x, y });
	}

	void BackGroundView::addBackGround(const BackGroundVM & bg)
	{
		m_bgs.push_back(bg);
	}

	void BackGroundView::draw(const s3d::Vec2& pos) const
	{
		ScopedRenderStates2D state(YClamp);
		for (const auto& bg : m_bgs) {
			bg.draw(pos);
		}
	}

}
