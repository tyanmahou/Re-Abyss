#pragma once
#include <typeindex>
#include <abyss/modules/ColSys/base/INode.hpp>
#include <abyss/modules/ColSys/base/IExtension.hpp>
#include <abyss/modules/ColSys/Result.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::ColSys
{
	/// <summary>
	/// 衝突ブランチ
	/// </summary>
	class Branch
	{
		static constexpr s3d::uint8 ActiveAll = static_cast<s3d::uint8>(~0);
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

		Branch& setActive(bool isActive, s3d::uint8 slot = 0)
		{
			if (isActive) {
				m_isActiveBit |= (1 << slot);
			} else {
				m_isActiveBit &= ~(1 << slot);
			}
			return *this;
		}

		bool isActive() const
		{
			if (m_nodes.empty()) {
				return false;
			}
			return (m_isActiveBit & ActiveAll) == ActiveAll;
		}

		void destroy()
		{
			m_isDestroyed = true;
		}
		bool isDestroyed() const
		{
			return m_isDestroyed;
		}

		const Result& result() const
		{
			return m_result;
		}
		
		template<class Node, class... Args>
		Branch& addNode(Args&&... args)
		{
			return this->addNode(std::make_unique<Node>(std::forward<Args>(args)...));
		}

		Branch& addNode(std::unique_ptr<INode>&& node);

		template<class Extension, class... Args>
		Branch& attach(Args&&... args)
		{
			return this->attach(typeid(Extension), std::make_unique<Extension>(std::forward<Args>(args)...));
		}
	private:
		Branch& attach(std::type_index type, std::unique_ptr<IExtension>&& extension);
	public:
		void onPreCollision();
		void onCollision(const Branch& other);
		bool isCollision(const Branch& other) const;
	private:
		s3d::Array<std::unique_ptr<INode>> m_nodes;
		s3d::uint64 m_id{};
		s3d::uint32 m_layer{};
		s3d::Optional<s3d::int32> m_toLayer;

		s3d::uint8 m_isActiveBit = ActiveAll;
		bool m_isDestroyed = false;

		Result m_result;
		s3d::HashTable<std::type_index, std::unique_ptr<IExtension>> m_extensions;
	};
}