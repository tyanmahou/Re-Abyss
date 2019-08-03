#include "ITileSet.hpp"
#include <Siv3D/TextureRegion.hpp>
using namespace s3d;

namespace s3dTiled
{
	TiledAnimation::TiledAnimation():
		m_stopwatch(true)
	{
	}

	void TiledAnimation::addFrame(TileId tileId, Duration duration)
	{
		m_frames.emplace_back(tileId, duration);
		m_maxDuration += duration;
	}

	TileId TiledAnimation::calcCurrentTileId()
	{
		int32 currentDuration = m_stopwatch.ms();
		if (currentDuration > m_maxDuration) {
			currentDuration = 0;
			m_stopwatch.restart();
		}
		int32 sumDuration = 0;
		for (const auto& frame : m_frames) {
			if (currentDuration < sumDuration + frame.second) {
				return frame.first;
			}
			sumDuration += frame.second;
		}
		return 0;
	}

	void ITileSet::setFirstGId(GId gId)
	{
		this->m_firstGId = gId;
	}

	void ITileSet::setTileCount(s3d::uint32 count)
	{
		this->m_tileCount = count;
	}

	void ITileSet::setColumns(s3d::uint32 columns)
	{
		this->m_columns = columns;
	}

	void ITileSet::addAnimation(TileId tileId, TiledAnimation&& animetion)
	{
		m_animations.emplace(tileId, std::move(animetion));
	}

	void ITileSet::addProps(TileId tileId, TiledProperties&& props)
	{
		m_props.emplace(tileId, std::move(props));
	}

	GId ITileSet::getFirstGId() const
	{
		return m_firstGId;
	}

	s3d::uint32 ITileSet::getTileCount() const
	{
		return m_tileCount;
	}

	bool ITileSet::isContain(GId gId) const
	{
		return m_firstGId <= gId && gId < m_firstGId + m_tileCount;
	}

	bool ITileSet::needAxisAjust() const
	{
		return m_needAxisAjust;
	}

	// UniformTileSet

	void UniformTileSet::setTileSize(const s3d::Size& tileSize)
	{
		this->m_tileSize = tileSize;
	}

	void UniformTileSet::setTexture(const s3d::Texture& texture)
	{
		m_texture = texture;
	}

	s3d::TextureRegion UniformTileSet::getTextureRegion(GId gId)
	{
		TileId tileId = gId - m_firstGId;
		if (m_animations.find(tileId) != m_animations.end()) {
			// アニメーションがある場合
			tileId = m_animations.at(tileId).calcCurrentTileId();
		}
		int32 x = tileId % m_columns;
		int32 y = tileId / m_columns;
		return m_texture({ m_tileSize.x * x, m_tileSize.y * y }, m_tileSize);
	}


	VariousTileSet::VariousTileSet()
	{
		this->m_needAxisAjust = true;
	}

	void VariousTileSet::addTexture(TileId tileId, const s3d::Texture& texture)
	{
		this->m_textures.emplace(tileId, texture);
		this->m_tileCount = Max(m_tileCount, tileId + 1u);
	}

	s3d::TextureRegion VariousTileSet::getTextureRegion(GId gId)
	{
		TileId tileId = gId - m_firstGId;
		if (m_animations.find(tileId) != m_animations.end()) {
			// アニメーションがある場合
			tileId = m_animations.at(tileId).calcCurrentTileId();
		}
		return m_textures[tileId];
	}

}