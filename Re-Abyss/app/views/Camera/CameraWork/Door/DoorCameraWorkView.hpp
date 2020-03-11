#pragma once
#include <memory>

#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class DoorCameraWorkView
	{
		const DoorCameraWork* const m_pWork;
	public:
		DoorCameraWorkView(const DoorCameraWork*const pCameraWork);
		void draw(const CameraView*const pCamera) const;
	};
}
