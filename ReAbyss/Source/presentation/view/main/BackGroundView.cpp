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
	BackGroundVM::BackGroundVM(const BackGroundEntity& data) :
		m_data(data)
	{}

	void BackGroundVM::draw(const s3d::Vec2& pos) const
	{
		const auto& screen = Constants::GameScreenSize;

		double u = m_data.loop.x ? (pos.x - screen.x / 2 - m_data.offset.x) / screen.x / m_data.rate.x : 0;
		double v = m_data.loop.y ? (pos.y - screen.y / 2 - m_data.offset.y) / screen.y / m_data.rate.y : 0;
		double x = m_data.loop.x ? pos.x : m_data.offset.x + m_data.texture.size().x / 2;
		double y = m_data.loop.y ? pos.y : m_data.offset.y + m_data.texture.size().y / 2;
		m_data.texture.uv(u, v, 1, 1).drawAt({ x, y });
	}

	void BackGroundView::addBackGround(const BackGroundVM & bg)
	{
		m_bgs.push_back(bg);
	}

	void BackGroundView::setPos(const s3d::Vec2 & pos)
	{
		m_pos = pos;
	}
	void BackGroundView::draw() const
	{
		ScopedRenderStates2D state(YClamp);
		for (const auto& bg : m_bgs) {
			bg.draw(m_pos);
		}
	}

}
