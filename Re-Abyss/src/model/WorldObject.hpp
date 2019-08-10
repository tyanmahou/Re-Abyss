#pragma once
#include "ICollider.hpp"

namespace abyss
{
	class WorldModel;

	class WorldObject : public ICollider
	{
	protected:
		WorldModel* m_pWorld = nullptr;

	public:
		WorldObject() = default;
		virtual ~ WorldObject() = default;

		void setWorld(WorldModel*const pWorld)
		{
			m_pWorld = pWorld;
		}

		virtual void update(double /*dt*/) {};
		virtual void draw()const {};
		virtual bool isDelete() const { return false; };
	};
}