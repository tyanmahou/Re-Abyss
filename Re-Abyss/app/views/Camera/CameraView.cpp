#include "CameraView.hpp"

#include <Siv3D.hpp>

#include <abyss/models/Camera/CameraModel.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss
{
	CameraView::CameraView(const CameraModel* const pCamera, const s3d::Vec2& quakeOffset) :
		m_pCamera(pCamera),
		m_quakeOffset(quakeOffset)
	{}

	const s3d::Vec2& CameraView::getCameraPos() const
	{
		return m_pCamera->getPos();
	}

	const s3d::Vec2& CameraView::getQuakeOffset() const
	{
		return m_quakeOffset;
	}

	void CameraView::drawDeathLine() const
	{
		constexpr ColorF colors[4] = { ColorF(0,0), ColorF(0,0) ,ColorF(0,1),ColorF(0,1) };
		const auto& currentRoom = m_pCamera->currentRoom();

		if (!currentRoom.passable(Forward::Down)) {
			auto region = currentRoom.getRegion();
			RectF(region.x, region.y + region.size.y - 40, region.w, 40).draw(colors);
		}
		const auto& nextRoom = m_pCamera->nextRoom();
		if (nextRoom && !nextRoom->passable(Forward::Down)) {
			auto region = nextRoom->getRegion();
			RectF(region.x, region.y + region.size.y - 40, region.w, 40).draw(colors);
		}
	}

	s3d::RectF CameraView::screenRegion() const
	{
		return s3d::RectF{ m_pCamera->getPos() - Constants::GameScreenSize / 2, Constants::GameScreenSize };
	}
    s3d::RectF CameraView::resolutionRegion() const
    {
        return s3d::RectF{ m_pCamera->getPos() - Constants::AppResolutionF / 2, Constants::AppResolutionF };
    }
	s3d::Vec2 CameraView::adjustTargetPos() const
	{
		s3d::Vec2 targetPos = m_pCamera->getTargetPos();
		double zoomScale = m_pCamera->getZoomScale();

		s3d::RectF region = this->screenRegion();
		auto tl = region.tl();
		auto br = region.br();
		auto harfSize = region.size / 2 / zoomScale;
		if (auto borderL = tl.x + harfSize.x;  targetPos.x < borderL) {
			// 左端
			targetPos.x = borderL;
		} else if (auto borderR = br.x - harfSize.x; targetPos.x > borderR) {
			// 右端
			targetPos.x = borderR;
		}
		if (auto borderT = tl.y + harfSize.y;  targetPos.y < borderT) {
			// 上端
			targetPos.y = borderT;
		} else if (auto borderB = br.y - harfSize.y; targetPos.y > borderB) {
			// 下端
			targetPos.y = borderB;
		}
		return targetPos;
	}
	s3d::Mat3x2 CameraView::getMat() const
	{
		static double scale = 1.0;
		scale += (KeyQ.pressed() - KeyW.pressed()) * Scene::DeltaTime();
		if (KeyR.down()) {
			scale = 1.0;
		}
		if (KeyT.down()) {
			scale = 2.0;
		}
		const_cast<CameraModel*>(m_pCamera)->setZoomScale(scale);
		auto targetPos = this->adjustTargetPos();
		auto cameraPos = -targetPos + (Constants::GameScreenSize / 2);
		return s3d::Mat3x2::Scale(m_pCamera->getZoomScale(), s3d::Round(targetPos)).translated(s3d::Round(cameraPos));
	}
	s3d::Transformer2D CameraView::getTransformer() const
	{
		return Transformer2D(this->getMat(), Transformer2D::Target::SetLocal);
	}
}
