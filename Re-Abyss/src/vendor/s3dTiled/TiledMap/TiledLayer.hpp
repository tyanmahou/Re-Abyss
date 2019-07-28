#pragma once
#include<Siv3D/Fwd.hpp>
#include<memory>

namespace s3dTiled
{
	class TiledSets;

	/// <summary>
	/// Tiled Layer
	/// </summary>
	class TiledLayer
	{
		friend class ImageLayer;
		friend class TileLayer;
		friend class ObjectLayer;
	public:
		enum class Type
		{
			Image,
			Tile,
			Object,
			None
		};
	private:
		class ITiledLayer;
		std::shared_ptr<ITiledLayer> pImpl;
	public:
		TiledLayer() = default;
		TiledLayer(s3d::XMLElement xml, const s3d::FilePath& parentPath);
		// TiledLayer(const s3d::JSONObject& json, const s3d::FilePath& parentPath);

		/// <summary>
		/// レイヤーの描画
		/// </summary>
		/// <param name="tileSets">タイルセット</param>
		/// <param name="rect">描画領域</param>
		/// <returns>true: 成功 false:失敗</returns>
		bool draw(const TiledSets& tileSets, const s3d::Rect& rect) const;

		/// <summary>
		/// レイヤータイプを取得
		/// </summary>
		/// <returns></returns>
		Type getType() const;
	};
}