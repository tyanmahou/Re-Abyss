#pragma once
#include "../../IView.hpp"

namespace abyss
{
	class WorldView;

	class IWorldObjectView : public IView
	{
	protected:
		WorldView* m_pWorldView = nullptr;
	public:
		virtual bool isDelete() const = 0;

		virtual void start() {}
		void setWorldView(WorldView* view)
		{
			m_pWorldView = view;
		}
	};
}