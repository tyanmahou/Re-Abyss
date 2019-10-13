#pragma once
#include <memory>
namespace abyss
{
	class CameraView;
	//class RoomMoveCameraWork;
	class DoorCameraWork;

	class ICameraWorkView
	{
	protected:
		const CameraView* const m_pCameraView = nullptr;
	public:
		ICameraWorkView(const CameraView* const);
		virtual ~ICameraWorkView();
		virtual void draw() const = 0;
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
