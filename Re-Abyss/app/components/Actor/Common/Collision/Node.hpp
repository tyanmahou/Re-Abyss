#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Collision/base/INode.hpp>

namespace abyss::Actor::Collision
{
	class Node final : public abyss::Collision::INode
	{
	public:
		Node(ActorObj* pActor, s3d::uint64 id);

		s3d::uint64 id() const override
		{
			return m_id;
		}

		void setLayer(s3d::uint32 layer)
		{
			m_layer = layer;
		}
		s3d::uint32 layer() const override
		{
			return m_layer;
		}
		void setToLayer(s3d::None_t none)
		{
			m_toLayer = none;
		}
		void setToLayer(s3d::uint32 toLayer)
		{
			m_toLayer = toLayer;
		}

		s3d::uint32 toLayer() const override
		{
			return m_toLayer.value_or(~m_layer);
		}

		bool isActive() const override;

		void destroy()
		{
			m_isDestroyed = true;
		}
		bool isDestroyed() const override
		{
			return m_isDestroyed;
		}

		const CShape& getShape() const override;

		void onPreCollision();
		void onCollision(const Ref<INode>& other) override;

	private:
		ActorObj* m_pActor = nullptr;
		s3d::uint64 m_id{};
		s3d::uint32 m_layer{};
		s3d::Optional<s3d::int32> m_toLayer;

		bool m_isActive = true;
		bool m_isDestroyed = false;
	};
}