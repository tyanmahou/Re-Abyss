#include <abyss/modules/Camera/Camera.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Camera/CameraTarget/CameraTargetCtrl.hpp>
#include <abyss/modules/Camera/CameraFix/CameraFixCtrl.hpp>
#include <abyss/modules/Camera/Quake/Quake.hpp>
#include <abyss/views/Camera/SnapshotView.hpp>
#include <abyss/commons/Constants.hpp>
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
		const Vec2& targetPos = m_target->update();

		// カメラ座標調整
		{
			// カメラ座標を補正
			Vec2 cameraPos = m_fixCtrl->apply(targetPos);
			// 地震適用
			m_quake->update(dt);

            m_camera->setPos(cameraPos);
			m_camera->setTargetPos(targetPos);
            m_camera->setZoomScale(m_target->zoomScale());
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

    const s3d::Vec2& Camera::getQuakeOffset() const
    {
        return m_quake->getOffset();
    }

	double Camera::getZoomScale() const
	{
		return m_camera->getZoomScale();
	}
	void Camera::setZoomScale(double scale) const
	{
		m_camera->setZoomScale(scale);
	}
	s3d::RectF Camera::screenRegion() const
	{
		return m_camera->screenRegion();
	}
	s3d::Vec2 Camera::transform(const s3d::Vec2& pos) const
	{
		return m_camera->getMat().transformPoint(pos);
	}
	SnapshotView* Camera::getSnapshot() const
	{
		return m_snapshot.get();
	}
}
