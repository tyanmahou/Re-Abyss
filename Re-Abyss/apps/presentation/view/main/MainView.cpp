#include "MainView.hpp"
#include <application/util/ScopedState.hpp>

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
	void MainView::addBackGroundView(const BackGroundVM& bg)
	{
		m_bg.addBackGround(bg);
	}
	void MainView::addLayerView(const s3d::String& layer, std::function<void(const s3d::RectF&)> view)
	{
		m_stageView.addView(layer, view);
	}
	void MainView::addWorldObjectView(std::unique_ptr<IWorldObjectView>&& view)
	{
		m_woldView.addView(std::move(view));
	}
	void MainView::update()
	{
		auto cameraPos = m_cameraView->getCameraPos();
		m_bg.setPos(cameraPos);
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

			m_bg.draw();

			// back
			m_stageView.draw(L"back", screen);

			m_cameraView->drawDeathLine();
			// map
			m_stageView.draw(L"map", screen);
			// door
			m_stageView.draw(L"door", screen);

			m_woldView.draw();

			//front
			m_stageView.draw(L"front", screen);

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
