#pragma once
#include<memory>
#include<presentation/view/main/BubbleGenerator.hpp>

namespace abyss
{
	class IMainPresenter;
	class IStageView;
	class CameraView;
	class ICameraWorkView;

	class IMainSceneView
	{
	protected:
		std::shared_ptr<IMainPresenter> m_presenter;
	public:
		IMainSceneView(const std::shared_ptr<IMainPresenter>& presenter):
			m_presenter(presenter)
		{}
		virtual ~IMainSceneView() = default;

		virtual void update(){}
		virtual void draw()const = 0;
	};

	class MainSceneView : public IMainSceneView
	{
		BubbleGenerator m_bubbles;

		std::unique_ptr<CameraView> m_cameraView;
		std::unique_ptr<ICameraWorkView> m_cameraWorkView;
		std::unique_ptr<IStageView> m_stageView;
	public:
		MainSceneView(const std::shared_ptr<IMainPresenter>& presenter);

		inline void setStageView(std::unique_ptr<IStageView>&& stageView)
		{
			this->m_stageView = std::move(stageView);
		}
		inline void setCameraView(std::unique_ptr<CameraView>&& cameraView)
		{
			this->m_cameraView = std::move(cameraView);
		}
		void update() override;
		void draw()const override;
	};
}