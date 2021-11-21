#pragma once
#include <abyss/modules/Collision/base/INode.hpp>
#include <abyss/modules/Collision/base/IExtension.hpp>
#include <abyss/modules/Collision/Result.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::Collision
{
	/// <summary>
	/// 衝突ブランチ
	/// </summary>
	class Branch
	{
	public:
		Branch(s3d::uint64 id);

		s3d::uint64 id() const
		{
			return m_id;
		}

		Branch& setLayer(s3d::uint32 layer)
		{
			m_layer = layer;
			return *this;
		}
		s3d::uint32 layer() const
		{
			return m_layer;
		}
		Branch& setToLayer(s3d::None_t)
		{
			m_toLayer = s3d::none;
			return *this;
		}
		Branch& setToLayer(s3d::uint32 toLayer)
		{
			m_toLayer = toLayer;
			return *this;
		}

		s3d::uint32 toLayer() const
		{
			return m_toLayer.value_or(~m_layer);
		}

		Branch& setActive(bool isActive)
		{
			m_isActive = isActive;
			return *this;
		}

		bool isActive() const
		{
			return m_isActive;
		}

		void destroy()
		{
			m_isDestroyed = true;
		}
		bool isDestroyed() const
		{
			return m_isDestroyed;
		}
	public:
		void onPreCollision();
		void onCollision(const Branch& other);
		bool isCollision(const Branch& other) const;
	private:
		s3d::Array<std::unique_ptr<INode>> m_nodes;
		s3d::uint64 m_id{};
		s3d::uint32 m_layer{};
		s3d::Optional<s3d::int32> m_toLayer;

		bool m_isActive = true;
		bool m_isDestroyed = false;

		Result m_result;
		s3d::HashTable<std::type_index, std::unique_ptr<IExtension>> m_extensions;
	};
}