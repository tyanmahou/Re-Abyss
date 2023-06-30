#include <abyss/modules/Camera/CameraParam.hpp>
#include <abyss/commons/Constants.hpp>
using namespace s3d;

namespace abyss
{
    s3d::Transformer2D CameraParam::Transformer(const s3d::Mat3x2& mat)
    {
        return s3d::Transformer2D(mat, TransformCursor::Yes, Transformer2D::Target::SetLocal);
    }
    CameraParam::CameraParam():
		m_pos(Constants::GameScreen.center()),
		m_targetPos(Constants::GameScreen.center())
	{}
	void CameraParam::setPos(const s3d::Vec2 pos)
	{
		m_pos = pos;
	}
	const s3d::Vec2& CameraParam::getPos() const
	{
		return m_pos;
	}
	void CameraParam::setTargetPos(const s3d::Vec2 pos)
	{
		m_targetPos = pos;
	}
	const s3d::Vec2& CameraParam::getTargetPos() const
	{
		return m_targetPos;
	}
	s3d::Vec2 CameraParam::tl() const
	{
        return getPos() - Constants::GameScreenSize / 2;
	}
    s3d::RectF CameraParam::screenRegion() const
    {
        return s3d::RectF{ getPos() - Constants::GameScreenSize / 2, Constants::GameScreenSize };
    }
    s3d::RectF CameraParam::resolutionRegion() const
    {
        return s3d::RectF{ getPos() - Constants::AppResolutionF / 2, Constants::AppResolutionF };
    }
    s3d::Vec2 CameraParam::adjustTargetPos() const
    {
        s3d::Vec2 targetPos = getTargetPos();
        double zoomScale = getZoomScale();

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
    s3d::Mat3x2 CameraParam::getMat() const
    {
        auto targetPos = this->adjustTargetPos();
        auto cameraPos = -targetPos + (Constants::GameScreenSize / 2);
        return s3d::Mat3x2::Scale(getZoomScale(), s3d::Round(targetPos))
            .translated(s3d::Round(cameraPos));
    }
    s3d::Transformer2D CameraParam::getTransformer() const
    {
        return Transformer(this->getMat());
    }
}
