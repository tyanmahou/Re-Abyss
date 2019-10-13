#include "MainSceneView.hpp"
#include <presentation/presenter/MainPresenter.hpp>

#include <presentation/view/main/CameraWorkView.hpp>
#include <presentation/view/main/CameraView.hpp>
#include <presentation/view/main/StageView.hpp>

#include <Siv3D.hpp>

namespace abyss
{
	MainSceneView::MainSceneView(const std::shared_ptr<IMainPresenter>& presenter):
		IMainSceneView(presenter)
	{
		// ドア移動のカメラワーク
		auto onStartDoorCameraWork = [this](const std::shared_ptr<DoorCameraWork>& work) {
			this->m_cameraWorkView = std::make_unique<DoorCameraWorkView>(this->m_cameraView.get(), work);
		};
		this->m_presenter->onStartDoorCameraWork().subscribe(onStartDoorCameraWork);
	}

	void MainSceneView::update()
	{
		auto cameraPos = m_cameraView->getCameraPos();
		m_bubbles.setPos(cameraPos);
		m_bubbles.update();

		if (m_cameraWorkView)
		{
			if (m_cameraWorkView->isEnd()) {
				m_cameraWorkView = nullptr;
			}
		}
	}

	void MainSceneView::draw() const
	{
		{
			auto t2d = m_cameraView->getTransformer();
			auto screen = m_cameraView->screenRegion();
			const auto& cameraPos = m_cameraView->getCameraPos();

			// 背景
			m_stageView->drawBg(cameraPos);

			// back
			m_stageView->drawLayer(U"back", screen);

			m_cameraView->drawDeathLine();
			// map
			m_stageView->drawLayer(U"map", screen);
			// door
			m_stageView->drawLayer(U"door", screen);

			//m_woldView.draw();

			//front
			m_stageView->drawLayer(U"front", screen);

			m_bubbles.draw();

			if (m_cameraWorkView) {
				m_cameraWorkView->draw();
			}
		}
	}
}
