#include "BackGroundVM.hpp"

#include <Siv3D/TextureRegion.hpp>

#include <abyss/commons/Constants.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
namespace abyss
{
    BackGroundVM::BackGroundVM(const s3d::String& path, const s3d::Vec2& offset, const s3d::Vector2D<bool>& loop, const s3d::Vec2& rate):
		m_texture(ResourceManager::Main()->loadTexture(path, Path::Root)),
		m_offset(offset),
		m_loop(loop),
		m_rate(rate)
    {}
    void BackGroundVM::draw(const s3d::Vec2& pos) const
	{
		const auto& screen = Constants::GameScreenSize;

		double u = m_loop.x ? (pos.x - screen.x / 2 - m_offset.x) / screen.x / m_rate.x : 0;
		double v = m_loop.y ? (pos.y - screen.y / 2 - m_offset.y) / screen.y / m_rate.y : 0;
		double x = m_loop.x ? pos.x : m_offset.x + m_texture.size().x / 2;
		double y = m_loop.y ? pos.y : m_offset.y + m_texture.size().y / 2;
		m_texture.uv(u, v, 1, 1).drawAt({ x, y });
	}
}
