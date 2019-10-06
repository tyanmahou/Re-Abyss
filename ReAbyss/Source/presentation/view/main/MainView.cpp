#include "MainView.hpp"
#include <Siv3D.hpp>

namespace abyss
{
	const MainViewFactory& MainView::getFactory() const
	{
		return m_viewFactory;
	}
	void MainView::createCameraView(const CameraModel& pCamera)
	{
		m_cameraView = std::make_unique<CameraView>(&pCamera);
	}
	void MainView::setCameraWorkView(std::unique_ptr<ICameraWorkView>&& view)
	{
		m_cameraWorkView = std::move(view);
	}
	MainView::MainView():
		m_viewFactory(this)
	{
	}
	void MainView::addWorldObjectView(std::unique_ptr<IWorldObjectView>&& view)
	{
		m_woldView.addView(std::move(view));
	}
	void MainView::update()
	{
		auto cameraPos = m_cameraView->getCameraPos();
		m_woldView.update();
		m_bubbles.setPos(cameraPos);
		m_bubbles.update();

		if (m_cameraWorkView)
		{
			if (m_cameraWorkView->isEnd()) {
				m_cameraWorkView = nullptr;
			}
		}
	}
	void MainView::draw() const
	{
		{
			auto t2d = m_cameraView->getTransformer();
			auto screen = m_cameraView->screenRegion();
			const auto& cameraPos = m_cameraView->getCameraPos();

			// ”wŒi
			m_stageView->drawBg(cameraPos);

			// back
			m_stageView->drawLayer(U"back", screen);

			m_cameraView->drawDeathLine();
			// map
			m_stageView->drawLayer(U"map", screen);
			// door
			m_stageView->drawLayer(U"door", screen);

			m_woldView.draw();

			//front
			m_stageView->drawLayer(U"front", screen);

			m_bubbles.draw();

			if (m_cameraWorkView) {
				m_cameraWorkView->draw();
			}
		}
	}
	CameraView* MainView::getCameraView() const
	{
		return m_cameraView.get();
	}
}
