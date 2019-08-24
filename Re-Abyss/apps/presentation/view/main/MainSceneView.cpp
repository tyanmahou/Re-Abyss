//#include "MainSceneView.h"
//#include "../../model/scene/MainSceneModel.hpp"
//#include "../../model/MapInfoModel.hpp"
//#include "../effects/Bubble.hpp"
//#include "../../util/ScopedState.hpp"
//
//#include <Siv3D.hpp>
//
//using namespace s3dTiled;
//using namespace abyss;
//namespace
//{
//	// clamp
//	constexpr SamplerState YClamp(
//		TextureAddressMode::Wrap,
//		TextureAddressMode::Clamp,
//		TextureAddressMode::Wrap,
//		TextureFilter::MinMagMipLinear
//	);
//}
//
//namespace abyss
//{
//	MainSceneView::MainSceneView(MainSceneModel* const pModel) :
//		m_pModel(pModel)
//	{
//		m_bubbleGenerator.setSpeed(0.1);
//
//		m_tiledMap.open(L"work/stage0/stage0.tmx");
//
//		// ”wŒiî•ñŽæ“¾
//		m_tiledMap.getLayer(L"bgs")->then(
//			[&](const GroupLayer & layer) {
//				for (const auto& child : layer.getLayers()) {
//					child.then([&](const ImageLayer & i) {
//						m_pModel->addBgModel(i);
//						});
//				}
//			}
//		);
//
//
//	}
//	MainSceneView::~MainSceneView()
//	{}
//
//	void MainSceneView::update()
//	{
//		int32 f = System::FrameCount();
//		if (f % 160 == 0) {
//			m_bubbleGenerator.add<BubbleEffect>(m_pModel->getCamera().getPos());
//		}
//	}
//
//	void MainSceneView::draw() const
//	{
//		const auto& camera = m_pModel->getCamera();
//		auto cameraPos = camera.getPos();
//		RectF rect = camera.screenRegion();
//
//		// in camera
//		{
//			auto t2d = camera.getTransformer();
//			// BG
//			{
//				abyss::ScopedRenderStates2D state(YClamp);
//				for (const auto& bg : m_pModel->getBgs()) {
//					bg.draw(cameraPos);
//				}
//			}
//			m_tiledMap.drawLayer(L"back", rect);
//
//			// dead line
//			camera.drawDeathLine();
//
//			m_tiledMap.drawLayer(L"map", rect);
//			m_tiledMap.drawLayer(L"door", rect);
//
//			// world;
//			m_pModel->getWorld().draw();
//
//			m_tiledMap.drawLayer(L"front", rect);
//			// bubble
//			{
//				abyss::ScopedRenderStates2D state(BlendState::Additive);
//
//				m_bubbleGenerator.update();
//			}
//
//			camera.drawCameraWork();
//		}
//		// UI
//	}
//}