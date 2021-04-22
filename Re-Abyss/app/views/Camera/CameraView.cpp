#include "CameraView.hpp"

#include <Siv3D.hpp>

#include <abyss/models/Camera/CameraModel.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss
{
	CameraView::CameraView(const CameraModel* const pCamera) :
		m_pCamera(pCamera)
	{}

	const s3d::Vec2& CameraView::getCameraPos() const
	{
		return m_pCamera->getPos();
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
	s3d::Mat3x2 CameraView::getMat() const
	{
		return s3d::Mat3x2::Translate(-m_pCamera->getPos()).translated(Constants::GameScreenSize / 2);
	}
	s3d::Transformer2D CameraView::getTransformer() const
	{
		return Transformer2D(this->getMat(), Transformer2D::Target::SetLocal);
	}
}
