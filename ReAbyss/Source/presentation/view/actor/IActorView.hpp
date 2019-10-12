#pragma once

namespace abyss
{
	class World;

	class IActorView
	{
	protected:
		World* m_pWorld;
	public:
		inline void setWorld(World* pWorld)
		{
			this->m_pWorld = pWorld;
		}
		virtual void start(){}
		virtual void draw()const = 0;
	};
}