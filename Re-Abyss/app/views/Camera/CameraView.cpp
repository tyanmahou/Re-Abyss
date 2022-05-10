#include <abyss/views/Camera/CameraView.hpp>

#include <Siv3D.hpp>

#include <abyss/models/Camera/CameraModel.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss
{
	s3d::Transformer2D CameraView::Transformer(const s3d::Mat3x2& mat)
	{
		return s3d::Transformer2D(mat, TransformCursor::Yes, Transformer2D::Target::SetLocal);
	}
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

	s3d::Vec2 CameraView::tl() const
	{
		return m_pCamera->getPos() - Constants::GameScreenSize / 2;
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
		auto targetPos = this->adjustTargetPos();
		auto cameraPos = -targetPos + (Constants::GameScreenSize / 2);
		return s3d::Mat3x2::Scale(m_pCamera->getZoomScale(), s3d::Round(targetPos))
			.translated(s3d::Round(cameraPos));
	}
	s3d::Transformer2D CameraView::getTransformer() const
	{
		return Transformer(this->getMat());
	}
}
