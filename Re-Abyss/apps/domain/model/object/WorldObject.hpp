#pragma once
#include "ICollider.hpp"

namespace abyss
{
	class WorldUseCase;

	class WorldObject : public ICollider
	{
	protected:
		WorldUseCase* m_pWorld = nullptr;
		s3d::uint64 m_id;
		bool m_isActive = true;
	public:
		WorldObject() = default;
		virtual ~ WorldObject() = default;

		void setWorld(WorldUseCase*const pWorld)
		{
			m_pWorld = pWorld;
		}
		void setId(s3d::uint64 id)
		{
			m_id = id;
		}
		s3d::uint64 getId() const
		{
			return m_id;
		}
		virtual void start() {};
		virtual void update(double /*dt*/) {};
		virtual void draw()const {};
		virtual bool isDelete() const { return false; };
	};
}