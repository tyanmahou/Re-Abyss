#pragma once
#include "../include/S3DTiled/TiledDef.hpp"
#include "../include/S3DTiled/TiledProperty.hpp"

#include<Siv3D/Stopwatch.hpp>
#include<Siv3D/Array.hpp>
#include<Siv3D/Vector2D.hpp>
#include<Siv3D/Texture.hpp>

namespace s3dTiled
{
	/// <summary>
	/// TiledAnimation
	/// </summary>
	class TiledAnimation
	{
	private:
		using Duration = s3d::int32;

		s3d::Stopwatch m_stopwatch;
		s3d::Array<std::pair<TileId, Duration>> m_frames;
		Duration m_maxDuration = 0;

	public:
		TiledAnimation();

		void addFrame(TileId tileId, Duration duration);
		TileId calcCurrentTileId();
	};

	class ITileSet
	{
	protected:
		GId m_firstGId;
		s3d::uint32 m_tileCount;
		s3d::uint32 m_columns;
		std::unordered_map<TileId, TiledAnimation> m_animations;
		std::unordered_map<TileId, TiledProperties> m_props;
		bool m_needAxisAjust = false;
	public:

		void setFirstGId(GId gId);
		void setTileCount(s3d::uint32 count);
		void setColumns(s3d::uint32 columns);

		void addAnimation(TileId tileId, TiledAnimation&& animetion);
		void addProps(TileId tileId, TiledProperties&& props);

		GId getFirstGId() const;

		s3d::uint32 getTileCount() const;

		bool isContain(GId gId) const;

		bool needAxisAjust() const;

		virtual s3d::TextureRegion getTextureRegion(GId gId) = 0;
	};

	/// <summary>
	/// 均一のタイルセット
	/// </summary>
	class UniformTileSet : public ITileSet
	{
	private:
		s3d::Size m_tileSize;
		s3d::Texture m_texture;
	public:
		UniformTileSet() = default;

		void setTileSize(const s3d::Size& tileSize);
		void setTexture(const s3d::Texture& texture);

		s3d::TextureRegion getTextureRegion(GId gId) override;
	};

	/// <summary>
	/// バラバラのタイルセット
	/// </summary>
	class VariousTileSet : public ITileSet
	{
	private:
		std::unordered_map<TileId, s3d::Texture> m_textures;
	public:
		VariousTileSet();

		void addTexture(TileId tileId, const s3d::Texture& texture);

		s3d::TextureRegion getTextureRegion(GId gId) override;
	};

}