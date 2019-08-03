#pragma once

#include "TiledTypes.hpp"
#include "TiledProperty.hpp"
#include "TiledObject.hpp"

#include<Siv3D/Texture.hpp>
#include<Siv3D/Grid.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>

#include <memory>
#include <functional>

namespace s3dTiled
{
	class TiledMap;

	class TiledLayerBase;
	class ImageLayer;
	class TileLayer;
	class ObjectGroup;

	enum class LayerType
	{
		ImageLayer,
		TileLayer,
		ObjectGroup,
		None
	};

	/// <summary>
	/// Tiled Layer
	/// </summary>
	class TiledLayer
	{
	private:
		std::shared_ptr<TiledLayerBase> pImpl;
	public:
		TiledLayer() = default;
		explicit TiledLayer(std::shared_ptr<TiledLayerBase> layer);

		/// <summary>
		/// レイヤーの描画
		/// </summary>
		/// <param name="map">タイルマップ</param>
		/// <param name="rect">描画領域</param>
		/// <returns>true: 成功 false:失敗</returns>
		bool draw(const TiledMap& map, const s3d::Rect& rect) const;

		/// <summary>
		/// レイヤータイプを取得
		/// </summary>
		/// <returns></returns>
		LayerType getType() const;

		/// <summary>
		/// レイヤーの名前を取得
		/// </summary>
		/// <returns></returns>
		const s3d::String& getName() const;

		/// <summary>
		/// プロパティを取得
		/// </summary>
		s3d::Optional<TiledProperty> getProperty(const s3d::String& key) const;

		/// <summary>
		/// 表示の有無を切り替える
		/// </summary>
		void setVisible(bool visible);

		/// <summary>
		/// 表示の有無を取得
		/// </summary>
		bool getVisible() const;

		/// <summary>
		/// レイヤータイプが ImageLayerの場合にコールバックを呼ぶ
		/// </summary>
		/// <param name="callback">コールバック</param>
		/// <returns>コールバックが呼ばれたらtrue</returns>
		bool then(std::function<void(const ImageLayer&)> callback) const;

		/// <summary>
		/// レイヤータイプが TileLayer の場合にコールバックを呼ぶ
		/// </summary>
		/// <param name="callback">コールバック</param>
		/// <returns>コールバックが呼ばれたらtrue</returns>
		bool then(std::function<void(const TileLayer&)> callback) const;

		/// <summary>
		/// レイヤータイプが ObjectGroup の場合にコールバックを呼ぶ
		/// </summary>
		/// <param name="callback">コールバック</param>
		/// <returns>コールバックが呼ばれたらtrue</returns>
		bool then(std::function<void(const ObjectGroup&)> callback) const;
	};

	class TiledLayerBase
	{
	protected:
		s3d::String m_name;
		s3d::Vec2 m_offset;
		TiledProperties m_props;
		bool m_visible = true;
	public:
		TiledLayerBase() = default;

		virtual ~TiledLayerBase() = default;
		virtual bool draw(const TiledMap& map, const s3d::Rect& rect) const = 0;
		virtual LayerType getType() const = 0;

		void setVisible(bool visible);
		bool getVisible() const;
		void setProps(TiledProperties&& props);
		s3d::Optional<TiledProperty> getProperty(const s3d::String& key) const;

		void setName(const s3d::String& name);
		const s3d::String& getName() const;

		void setOffset(const s3d::Vec2& offset);
	};
	/// <summary>
	/// ImageLayer
	/// </summary>
	class ImageLayer : public TiledLayerBase
	{
	private:
		s3d::Texture m_texture;
	public:
		void setTexture(s3d::Texture texture);

		bool draw(const TiledMap& map, const s3d::Rect& rect) const override;
		LayerType getType() const override;
	};

	/// <summary>
	/// TileLayer
	/// </summary>
	class TileLayer : public TiledLayerBase
	{
	private:
		s3d::Grid<GId> m_gIds;
	public:
		TileLayer() = default;
		void setGrid(s3d::Grid<GId>&& grid);
		const s3d::Grid<GId>& getGrid() const;

		bool draw(const TiledMap& map, const s3d::Rect& rect) const override;
		LayerType getType() const override;
	};

	/// <summary>
	/// Object Group
	/// </summary>
	class ObjectGroup : public TiledLayerBase
	{
	private:
		s3d::Array<TiledObject> m_objects;

	public:
		ObjectGroup() = default;

		void addObject(TiledObject&& obj);
		const s3d::Array<TiledObject>& getObjects() const;

		bool draw(const TiledMap& map, const s3d::Rect& rect) const override;

		LayerType getType() const override;
	};
}