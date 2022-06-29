#include <abyss/modules/Camera/Camera.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Camera/CameraTarget/CameraTargetCtrl.hpp>
#include <abyss/modules/Camera/CameraFix/CameraFixCtrl.hpp>
#include <abyss/modules/Camera/Quake/Quake.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Camera/SnapshotView.hpp>

#include <Siv3D.hpp>

namespace abyss
{
	Camera::Camera():
		m_camera(std::make_unique<CameraParam>()),
		m_target(std::make_unique<CameraTargetCtrl>()),
		m_fixCtrl(std::make_unique<CameraFixCtrl>()),
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
			// カメラ座標を補正
			Vec2 cameraPos = m_fixCtrl->apply(targetPos);

			// 地震適用
			m_quake->update(dt);

			m_camera->setPos(Math::Round(cameraPos));
			m_camera->setTargetPos(Math::Round(targetPos));
		}
	}

	const s3d::Vec2& Camera::getPos() const
	{
		return m_camera->getPos();
	}

	void Camera::addTarget(const std::shared_ptr<ICameraTarget>& target)
	{
		m_target->add(target);
	}

	void Camera::addCameraFix(const std::shared_ptr<ICameraFix>& fix)
	{
		m_fixCtrl->add(fix);
	}

	void Camera::removeCameraFix(const std::shared_ptr<ICameraFix>&fix)
	{
		m_fixCtrl->remove(fix);
	}

	Ref<QuakeEpicenter> Camera::startQuake(double maxOffset, double timeSec)
	{
		auto quake = std::make_shared<QuakeEpicenter>(maxOffset, timeSec);
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

	double Camera::getZoomScale() const
	{
		return m_camera->getZoomScale();
	}
	void Camera::setZoomScale(double scale) const
	{
		m_camera->setZoomScale(scale);
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
		return this->createView().getMat().transformPoint(pos);
	}
	SnapshotView* Camera::getSnapshot() const
	{
		return m_snapshot.get();
	}
}
