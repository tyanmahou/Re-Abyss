#pragma once
#include "../IView.hpp"
#include <memory>
namespace abyss
{
	class CameraView;
	//class RoomMoveCameraWork;
	class DoorCameraWork;

	class ICameraWorkView: public IView
	{
	protected:
		const CameraView* const m_pCameraView = nullptr;
	public:
		ICameraWorkView(const CameraView* const);

		virtual bool isEnd()const = 0;
	};

	class DoorCameraWorkView : public ICameraWorkView
	{
		std::weak_ptr<DoorCameraWork> m_pWork;
	public:
		DoorCameraWorkView(const CameraView* const, const std::shared_ptr<DoorCameraWork>&);
		void draw()const override;
		bool isEnd()const override;
	};
}
