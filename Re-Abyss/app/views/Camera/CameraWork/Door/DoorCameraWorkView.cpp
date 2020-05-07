#include "DoorCameraWorkView.hpp"
#include <abyss/controllers/Camera/CameraWork/Door/DoorCameraWork.hpp>
#include <abyss/views/Camera/CameraView.hpp>

#include <abyss/views/Fade/Fade.hpp>

namespace abyss
{
	DoorCameraWorkView::DoorCameraWorkView(const DoorCameraWork* const pCameraWork):
		m_pWork(pCameraWork)
	{}
	void DoorCameraWorkView::draw(const CameraView* const pCamera) const
	{
		using State = DoorCameraWork::State;

		if (m_pWork->m_state == State::FadeIn) {
			FadeIn(Fade::SmoothCircle, m_pWork->fadeIn0_1(), pCamera->resolutionRegion(), m_pWork->m_playerMove.second);
		} else {
			FadeOut(Fade::SmoothCircle, m_pWork->fadeOut0_1(), pCamera->resolutionRegion(), m_pWork->m_playerMove.first);
		}
	}
}