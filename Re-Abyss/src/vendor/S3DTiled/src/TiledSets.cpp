#pragma once
#include "../include/S3DTiled/TiledSets.hpp"
#include "ITileSet.hpp"
#include <Siv3D/TextureRegion.hpp>

using namespace s3d;

namespace s3dTiled
{
	class TiledSets::CTiledSets
	{
		friend class TiledSets;

		Array<std::unique_ptr<ITileSet>> m_tileSets;
		std::unordered_map<GId, uint32> m_gIdTileIndexMap; // gIdからtileセットへの検索をO(1)にします
		Size m_tileSize;

	public:
		void addTileSet(std::unique_ptr<ITileSet>&& tileSet)
		{
			m_tileSets.push_back(std::move(tileSet));

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

	void TiledSets::addTileSet(std::unique_ptr<ITileSet>&& tileSet) const
	{
		pImpl->addTileSet(std::move(tileSet));
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