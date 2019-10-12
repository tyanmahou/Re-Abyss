#pragma once

namespace abyss
{
	class WorldView;

	class IActorView
	{
	protected:
		WorldView* m_pWorld;
	public:
		inline void setWorld()
		{

		}
		virtual void draw()const = 0;
	};
}