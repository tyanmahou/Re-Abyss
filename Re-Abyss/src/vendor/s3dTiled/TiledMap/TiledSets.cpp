#pragma once
#include "TiledSets.hpp"
#include<Siv3D.hpp>

using namespace s3dTiled;

namespace
{
	/// <summary>
	/// Animation
	/// </summary>
	class TiledAnimation
	{
		using Duration = int32;

		Stopwatch m_stopwatch;
		Array<std::pair<TileId, Duration>> m_frames;
		Duration m_maxDuration = 0;

	public:
		TiledAnimation(XMLElement xml) :
			m_stopwatch(true)
		{
			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() != L"frame") {
					continue;
				}
				int32 duration = Parse<int32>(elm.attribute(L"duration").value_or(L"0"));
				m_maxDuration += duration;
				m_frames.emplace_back(
					Parse<TileId>(elm.attribute(L"tileid").value_or(L"0")),
					duration
				);
			}
		}
		TileId calcCurrentTileId()
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
	};

	class ITileSet
	{
	protected:
		GId m_firstGId;
		uint32 m_tileCount;
		uint32 m_columns;
		std::unordered_map<TileId, TiledAnimation> m_animations;
		bool m_needAxisAjust = false;
	public:
		ITileSet(XMLElement xml) :
			m_firstGId(Parse<GId>(xml.attribute(L"firstgid").value_or(L"0"))),
			m_tileCount(Parse<uint32>(xml.attribute(L"tilecount").value_or(L"0"))),
			m_columns(Parse<uint32>(xml.attribute(L"columns").value_or(L"0")))
		{
			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"tile") {
					int tileId = Parse<TileId>(elm.attribute(L"id").value_or(L"0"));
					for (auto animation = elm.firstChild(); animation; animation = animation.nextSibling()) {
						if (animation.name() == L"animation") {
							m_animations.emplace(tileId, animation);
						}
					}
				}
			}
		}

		GId getFirstGId() const
		{
			return m_firstGId;
		}
		uint32 getTileCount() const
		{
			return m_tileCount;
		}
		bool isContain(GId gId) const
		{
			return m_firstGId <= gId && gId < m_firstGId + m_tileCount;
		}

		bool needAxisAjust() const
		{
			return m_needAxisAjust;
		}
		virtual TextureRegion getTextureRegion(int32 gId) = 0;
	};

	/// <summary>
	/// 均一のタイルセット
	/// </summary>
	class UniformTileSet : public ITileSet
	{
	private:
		Size m_tileSize;
		Texture m_texture;
	public:
		UniformTileSet() = default;
		UniformTileSet(XMLElement xml, const  FilePath& parentPath) :
			ITileSet(xml),
			m_tileSize(
				Parse<int32>(xml.attribute(L"tilewidth").value_or(L"0")),
				Parse<int32>(xml.attribute(L"tileheight").value_or(L"0"))
			)
		{
			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"image") {
					m_texture = Texture(parentPath + elm.attribute(L"source").value_or(L""));
					break;
				}
			}
		}

		TextureRegion getTextureRegion(int32 gId) override
		{
			int32 tileId = gId - m_firstGId;
			if (m_animations.find(tileId) != m_animations.end()) {
				// アニメーションがある場合
				tileId = m_animations.at(tileId).calcCurrentTileId();
			}
			int32 x = tileId % m_columns;
			int32 y = tileId / m_columns;
			return m_texture({ m_tileSize.x * x, m_tileSize.y * y }, m_tileSize);
		}
	};

	/// <summary>
	/// バラバラのタイルセット
	/// </summary>
	class VariousTileSet : public ITileSet
	{
	private:
		std::unordered_map<TileId, Texture> m_textures;
	public:
		VariousTileSet() = default;
		VariousTileSet(XMLElement xml, const  FilePath& parentPath) :
			ITileSet(xml)
		{
			this->m_needAxisAjust = true;

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"tile") {
					int tileId = Parse<int32>(elm.attribute(L"id").value_or(L"0"));
					for (auto image = elm.firstChild(); image; image = image.nextSibling()) {
						if (image.name() == L"image") {
							m_textures.emplace(tileId, parentPath + image.attribute(L"source").value_or(L""));
							m_tileCount = Max(m_tileCount, tileId + 1u);
							break;
						}
					}
				}
			}
		}

		TextureRegion getTextureRegion(int32 gId) override
		{
			int32 tileId = gId - m_firstGId;
			if (m_animations.find(tileId) != m_animations.end()) {
				// アニメーションがある場合
				tileId = m_animations.at(tileId).calcCurrentTileId();
			}
			return m_textures[tileId];
		}
	};
}
namespace s3dTiled
{
	class TiledSets::CTiledSets
	{
		friend class TiledSets;

		Array<std::unique_ptr<ITileSet>> m_tileSets;
		std::unordered_map<GId, uint32> m_gIdTileIndexMap; // gidからtileセットへの検索をO(1)にします
		Size m_tileSize;

	public:
		void pushTileSet(XMLElement xml, const s3d::FilePath& parentPath)
		{
			if (xml.attribute(L"columns").value_or(L"0") == L"0") {
				m_tileSets.push_back(std::make_unique<VariousTileSet>(xml, parentPath));
			}
			else {
				m_tileSets.push_back(std::make_unique<UniformTileSet>(xml, parentPath));
			}

			// gIdからtilesetへのマッピングを作成
			const auto& last = m_tileSets.back();
			for (TileId id = 0; id < last->getTileCount(); ++id) {
				m_gIdTileIndexMap[last->getFirstGId() + id] = m_tileSets.size() - 1;
			}
		}
		ITileSet* getTileSet(GId gId) const
		{
			return m_tileSets[m_gIdTileIndexMap.at(gId)].get();
		}

	};

	TiledSets::TiledSets():
		pImpl(std::make_shared<CTiledSets>())
	{}
	s3d::TextureRegion TiledSets::getTile(GId gId) const
	{
		return pImpl->getTileSet(gId)->getTextureRegion(gId);
	}
	void TiledSets::pushTileSet(XMLElement xml, const s3d::FilePath& parentPath) const
	{
		pImpl->pushTileSet(xml, parentPath);
	}
	bool TiledSets::needAxisAdjust(GId gId) const
	{
		return pImpl->getTileSet(gId)->needAxisAjust();
	}
	void TiledSets::setTileSize(const s3d::Size& size) const
	{
		pImpl->m_tileSize = size;
	}
	Size TiledSets::getTileSize() const
	{
		return pImpl->m_tileSize;
	}
}