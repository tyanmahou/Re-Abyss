#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class IActorView
	{
	protected:
		WorldView* const m_pWorldView;
	public:
		IActorView(WorldView* const pWorldView);
		IActorView(const IActor* const pActor);
		virtual void start() {}
		virtual void draw()const = 0;
	};
}