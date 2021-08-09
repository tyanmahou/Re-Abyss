#include "Camera.hpp"

#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/models/Camera/QuakeModel.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Camera/CameraTarget/CameraTargetCtrl.hpp>
#include <abyss/modules/Camera/Quake/Quake.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Camera/SnapshotView.hpp>

#include <Siv3D.hpp>

namespace abyss
{
	Camera::Camera():
		m_camera(std::make_unique<CameraModel>()),
		m_target(std::make_unique<CameraTargetCtrl>()),
		m_quake(std::make_unique<Quake>()),
		m_snapshot(std::make_unique<SnapshotView>())
	{}

	Camera::~Camera()
	{}

	void Camera::setManager(Manager * pManager)
	{
		m_pManager = pManager;
	}

	void Camera::update(double dt)
	{
		const Vec2& targetPos = m_target->update(dt);

		// カメラ座標調整
		{
			Vec2 cameraPos = targetPos;
			//Vec2 cameraPos = m_camera
			//	->currentRoom()
			//	.cameraBorderAdjusted(targetPos);

			// 地震適用
			m_quake->update(dt);

			m_camera->setPos(Math::Round(cameraPos));
			m_camera->setTargetPos(Math::Round(targetPos));
		}
	}
	void Camera::setPos(const s3d::Vec2& cameraPos) const
	{
		m_camera->setPos(Math::Round(cameraPos));
	}
	const s3d::Vec2& Camera::getPos() const
	{
		return m_camera->getPos();
	}

	void Camera::addTarget(const std::shared_ptr<ICameraTarget>& target)
	{
		m_target->add(target);
	}

	Ref<QuakeModel> Camera::startQuake(double maxOffset, double timeSec)
	{
		auto quake = std::make_shared<QuakeModel>(maxOffset, timeSec);
		m_quake->add(quake);
		return quake;
	}
	void Camera::stopQuake()
	{
		m_quake->stopAll();
	}
	bool Camera::isQuake() const
	{
		return !m_quake->isEnd();
	}

	CameraView Camera::createView() const
	{
		return CameraView(m_camera.get(), m_quake->getOffset());
	}
	s3d::RectF Camera::screenRegion() const
	{
		return this->createView().screenRegion();
	}
	s3d::Vec2 Camera::transform(const s3d::Vec2& pos) const
	{
		return this->createView().getMat().transform(pos);
	}
	SnapshotView* Camera::getSnapshot() const
	{
		return m_snapshot.get();
	}
}