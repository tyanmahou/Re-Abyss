#pragma once
#include"TiledDef.hpp"
#include<Siv3D/Fwd.hpp>

#include<memory>

namespace s3dTiled
{
	class TiledSets
	{
		class CTiledSets;
		std::shared_ptr<CTiledSets> pImpl;
	public:
		TiledSets();

		s3d::TextureRegion getTile(GId gId) const;

		void pushTileSet(s3d::XMLElement xml, const s3d::FilePath& parentPath) const;
		/// <summary>
		/// ���␳���K�v���ǂ���
		/// </summary>
		/// <param name="gId">�O���[�o��Id</param>
		/// <returns></returns>
		bool needAxisAdjust(GId gId) const;

		void setTileSize(const s3d::Size& size) const;

		s3d::Size getTileSize() const;
	};
}