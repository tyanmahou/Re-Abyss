#pragma once
#include "ICollider.hpp"
#include <abyss/visitors/ActVisitor.hpp>

namespace abyss
{
	class IActor : public ICollider
	{
	protected:
		World* m_pWorld = nullptr;
		s3d::uint64 m_id;
		bool m_isActive = true;

	public:
		IActor() = default;
		virtual ~IActor() = default;

		inline void setWorld(World* const pWorld)
		{
			m_pWorld = pWorld;
		}
		inline World* getWorld() const
		{
			return m_pWorld;
		}
		inline void setId(s3d::uint64 id)
		{
			m_id = id;
		}
		inline s3d::uint64 getId() const
		{
			return m_id;
		}
		inline virtual void start() {}
		inline virtual void update([[maybe_unused]]double dt) {}
		inline virtual void lastUpdate([[maybe_unused]] double dt) {}
		inline virtual void draw()const {}

		inline void setActive(bool active)
		{
			m_isActive = active;
		}
		inline void destroy()
		{
			this->setActive(false);
		}
		inline bool isDelete() const
		{
			return !m_isActive;
		}

		bool accept(const ActVisitor& visitor) override;
	};
}