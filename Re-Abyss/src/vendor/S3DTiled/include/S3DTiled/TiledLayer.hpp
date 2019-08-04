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
	class GroupLayer;

	enum class LayerType
	{
		ImageLayer,
		TileLayer,
		ObjectGroup,
		GroupLayer,
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
		/// ���C���[�̕`��
		/// </summary>
		/// <param name="map">�^�C���}�b�v</param>
		/// <param name="rect">�`��̈�</param>
		/// <returns>true: ���� false:���s</returns>
		bool draw(const TiledMap& map, const s3d::Rect& rect) const;

		/// <summary>
		/// ���C���[�^�C�v���擾
		/// </summary>
		/// <returns></returns>
		LayerType getType() const;

		/// <summary>
		/// ���C���[�̖��O���擾
		/// </summary>
		/// <returns></returns>
		const s3d::String& getName() const;

		/// <summary>
		/// �v���p�e�B���擾
		/// </summary>
		s3d::Optional<TiledProperty> getProperty(const s3d::String& key) const;

		/// <summary>
		/// �\���̗L����؂�ւ���
		/// </summary>
		void setVisible(bool visible);

		/// <summary>
		/// �\���̗L�����擾
		/// </summary>
		bool getVisible() const;

		/// <summary>
		/// ���C���[�^�C�v�� ImageLayer�̏ꍇ�ɃR�[���o�b�N���Ă�
		/// </summary>
		/// <param name="callback">�R�[���o�b�N</param>
		/// <returns>�R�[���o�b�N���Ă΂ꂽ��true</returns>
		bool then(std::function<void(const ImageLayer&)> callback) const;

		/// <summary>
		/// ���C���[�^�C�v�� TileLayer �̏ꍇ�ɃR�[���o�b�N���Ă�
		/// </summary>
		/// <param name="callback">�R�[���o�b�N</param>
		/// <returns>�R�[���o�b�N���Ă΂ꂽ��true</returns>
		bool then(std::function<void(const TileLayer&)> callback) const;

		/// <summary>
		/// ���C���[�^�C�v�� ObjectGroup �̏ꍇ�ɃR�[���o�b�N���Ă�
		/// </summary>
		/// <param name="callback">�R�[���o�b�N</param>
		/// <returns>�R�[���o�b�N���Ă΂ꂽ��true</returns>
		bool then(std::function<void(const ObjectGroup&)> callback) const;

		/// <summary>
		/// ���C���[�^�C�v�� GroupLayer �̏ꍇ�ɃR�[���o�b�N���Ă�
		/// </summary>
		/// <param name="callback">�R�[���o�b�N</param>
		/// <returns>�R�[���o�b�N���Ă΂ꂽ��true</returns>
		bool then(std::function<void(const GroupLayer&)> callback) const;
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
		const s3d::Vec2& getOffset() const;
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
		const s3d::Texture& getTexture() const;

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

	/// <summary>
	/// GroupLayer
	/// </summary>
	class GroupLayer : public TiledLayerBase
	{
	private:
		s3d::Array<TiledLayer> m_layers;

	public:
		GroupLayer() = default;
		void addLayer(const TiledLayer& layer);
		const s3d::Array<TiledLayer>&  getLayers() const;

		bool draw(const TiledMap& map, const s3d::Rect& rect) const override;

		LayerType getType() const override;
	};
}