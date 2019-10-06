#pragma once
#include <S3DTiled.hpp>
#include <Siv3D/Effect.hpp>
#include "../IView.hpp"
#include "WorldView.hpp"
#include "MainViewFactory.hpp"
#include "BubbleGenerator.hpp"
#include "BackGroundView.hpp"

#include "CameraView.hpp"
#include "CameraWorkView.hpp"
#include "StageLayerView.hpp"

namespace abyss
{
	class CameraModel;
	class CameraView;
	class ICameraWorkView;

	class IMainView : public IView
	{
	public:
		virtual void addBackGroundView(const BackGroundVM& bg) = 0;
		virtual void addLayerView(const s3d::String& layer, std::function<void(const s3d::RectF&)>) = 0;
		virtual void addWorldObjectView(std::unique_ptr<IWorldObjectView>&& view) = 0;
		virtual const MainViewFactory& getFactory()const = 0;

		virtual void createCameraView(const CameraModel& pCamera) = 0;
		virtual void setCameraWorkView(std::unique_ptr<ICameraWorkView>&& view) = 0;
	};

	class MainView : public IMainView
	{
	private:
		BackGroundView m_bg;

		WorldView m_woldView;
		MainViewFactory m_viewFactory;

		BubbleGenerator m_bubbles;

		std::unique_ptr<CameraView> m_cameraView;
		std::unique_ptr<ICameraWorkView> m_cameraWorkView;
		StageLayerView m_stageView;

	public:
		MainView();

		void addBackGroundView(const BackGroundVM& bg)override;
		void addLayerView(const s3d::String& layer, std::function<void(const s3d::RectF&)> view)override;
		void addWorldObjectView(std::unique_ptr<IWorldObjectView>&& view) override;
		const MainViewFactory& getFactory()const override;
		void createCameraView(const CameraModel& pCamera)override;
		void setCameraWorkView(std::unique_ptr<ICameraWorkView>&& view)override;

		void update() override;
		void draw()const;

		CameraView* getCameraView()const;
	};
}