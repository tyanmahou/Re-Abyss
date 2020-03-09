#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class IActorView
	{
	protected:
		WorldView* m_pWorld;
	public:
		inline void setWorld(WorldView* pWorld)
		{
			this->m_pWorld = pWorld;
		}
		virtual void start() {}
		virtual void draw()const = 0;
	};
}