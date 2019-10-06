#include "TileSetBase.hpp"

#include <Siv3D/TextureRegion.hpp>
using namespace s3d;

namespace s3dTiled
{
	// TiledAnimation

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

	// TileSetBase

	void TileSetBase::setFirstGId(GId gId)
	{
		this->m_firstGId = gId;
	}

	void TileSetBase::setTileCount(s3d::uint32 count)
	{
		this->m_tileCount = count;
	}

	void TileSetBase::setColumns(s3d::uint32 columns)
	{
		this->m_columns = columns;
	}

	void TileSetBase::addAnimation(TileId tileId, TiledAnimation&& animetion)
	{
		m_animations.emplace(tileId, std::move(animetion));
	}

	void TileSetBase::addProps(TileId tileId, TiledProperties&& props)
	{
		m_props.emplace(tileId, std::move(props));
	}

	s3d::Optional<TiledProperty> TileSetBase::getProperty(GId gId, const s3d::String& key) const
	{
		TileId tileId = gId - m_firstGId;

		if (m_props.find(tileId) == m_props.end()) {
			return s3d::none;
		}
		const auto& props = m_props.at(tileId);

		if (props.find(key) == props.end()) {
			return s3d::none;
		}
		return props.at(key);
	}

	GId TileSetBase::getFirstGId() const
	{
		return m_firstGId;
	}

	s3d::uint32 TileSetBase::getTileCount() const
	{
		return m_tileCount;
	}

	bool TileSetBase::isContain(GId gId) const
	{
		return m_firstGId <= gId && gId < m_firstGId + m_tileCount;
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