#pragma once
#include"TiledDef.hpp"

#include<memory>

namespace s3dTiled
{
	class ITileSet;

	class TiledSets
	{
		class CTiledSets;
		std::shared_ptr<CTiledSets> pImpl;
	public:
		TiledSets();

		s3d::TextureRegion getTile(GId gId) const;

		void addTileSet(std::unique_ptr<ITileSet>&& tileSet) const;

		/// <summary>
		/// 軸補正が必要かどうか
		/// </summary>
		/// <param name="gId">グローバルId</param>
		/// <returns></returns>
		bool needAxisAdjust(GId gId) const;

		void setTileSize(const s3d::Size& size) const;

		s3d::Size getTileSize() const;
	};
}