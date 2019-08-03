#pragma once

#include "TiledDef.hpp"
#include "TiledProperty.hpp"
#include "TiledObject.hpp"

#include<Siv3D/Texture.hpp>
#include<Siv3D/Grid.hpp>
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>

#include <memory>

namespace s3dTiled
{
	class TiledSets;
	class ILayer;

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
		std::shared_ptr<ILayer> pImpl;
	public:
		TiledLayer() = default;
		explicit TiledLayer(std::shared_ptr<ILayer> layer);

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
		LayerType getType() const;
		const s3d::String& getName() const;
	};

	class ILayer
	{
	protected:
		s3d::String m_name;
		s3d::Vec2 m_offset;
		TiledProperties m_props;
		bool m_visible = true;
	public:
		ILayer() = default;

		virtual ~ILayer() = default;
		virtual bool draw(const TiledSets& tileSets, const s3d::Rect& rect) const = 0;
		virtual LayerType getType() const = 0;

		void setVisible(bool visible);
		void setProps(TiledProperties&& props);
		void setName(const s3d::String& name);
		const s3d::String& getName() const;
		void setOffset(const s3d::Vec2& offset);
	};
	/// <summary>
	/// ImageLayer
	/// </summary>
	class ImageLayer : public ILayer
	{
	private:
		s3d::Texture m_texture;
	public:
		void setTexture(s3d::Texture texture);

		bool draw(const TiledSets& tileSets, const s3d::Rect& rect) const override;
		LayerType getType() const override;
	};

	/// <summary>
	/// TileLayer
	/// </summary>
	class TileLayer : public ILayer
	{
	private:
		s3d::Grid<GId> m_gIds;
	public:
		TileLayer() = default;
		void setGrid(s3d::Grid<GId>&& grid);

		bool draw(const TiledSets& tileSets, const s3d::Rect& rect) const override;
		LayerType getType() const override;
	};

	/// <summary>
	/// Object Group
	/// </summary>
	class ObjectGroup : public ILayer
	{
	private:
		s3d::Array<TiledObject> m_objects;

	public:
		ObjectGroup() = default;

		void addObject(TiledObject&& obj);

		bool draw(const TiledSets& tileSets, const s3d::Rect& rect) const override;

		LayerType getType() const override;
	};
}