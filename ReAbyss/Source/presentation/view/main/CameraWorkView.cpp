#include "CameraWorkView.hpp"
#include <domain/model/CameraWork.hpp>
#include <presentation/view/main/CameraView.hpp>
#include <presentation/view/fade/Fade.hpp>
#include <presentation/view/main/MainView.hpp>
#include <presentation/view/main/MainViewFactory.hpp>

namespace abyss
{
	ICameraWorkView::ICameraWorkView(const CameraView* const pCameraView) :
		m_pCameraView(pCameraView)
	{}
	DoorCameraWorkView::DoorCameraWorkView(const CameraView* const pCameraView, const std::shared_ptr<DoorCameraWork>& pWork) :
		ICameraWorkView(pCameraView),
		m_pWork(pWork)
	{
	}
	void DoorCameraWorkView::draw() const
	{
		auto work = m_pWork.lock();

		using State = DoorCameraWork::State;

		if (work->m_state == State::FadeIn) {
			FadeIn(Fade::SmoothCircle, work->fadeIn0_1(), m_pCameraView->screenRegion(), work->m_playerMove.second);
		}
		else {
			FadeOut(Fade::SmoothCircle, work->fadeOut0_1(), m_pCameraView->screenRegion(), work->m_playerMove.first);
		}
	}
	bool DoorCameraWorkView::isEnd() const
	{
		return m_pWork.expired();
	}

	//template<>
	//struct MainViewFactory<DoorCameraWork>
	//{
	//	auto operator()(MainView* main, const std::shared_ptr<DoorCameraWork>& model)const {

	//		auto view = std::make_unique<DoorCameraWorkView>(main->getCameraView(), model);
	//		return view;
	//	}
	//};
}