#include "MainSceneView.h"
#include "../../model/scene/MainSceneModel.hpp"
#include "../effects/Bubble.hpp"
#include "../../util/ScopedState.hpp"

#include <Siv3D.hpp>

namespace
{
	// clamp
	constexpr SamplerState YClamp(
		TextureAddressMode::Wrap,
		TextureAddressMode::Clamp,
		TextureAddressMode::Wrap,
		TextureFilter::MinMagMipLinear
	);

}
using namespace s3dTiled;

namespace abyss
{
	MainSceneView::MainSceneView(MainSceneModel* const pModel) :
		m_pModel(pModel)
	{
		m_bubbleGenerator.setSpeed(0.1);

		m_tiledMap.open(L"work/stage0/stage0.tmx");

		// •”‰®î•ñŽæ“¾
		m_tiledMap.getLayer(L"room")->then(
			[this](const ObjectGroup & layer) {
				for (const auto& obj : layer.getObjects()) {
					m_pModel->addRoom(obj);
				}
			}
		);
		// ”wŒiî•ñŽæ“¾
		m_tiledMap.getLayer(L"bgs")->then(
			[&](const GroupLayer & layer) {
				for (const auto& child : layer.getLayers()) {
					child.then([&](const ImageLayer & i) {
						m_pModel->addBgModel(i);
					});
				}
			}
		);
	}
	MainSceneView::~MainSceneView()
	{}

	void MainSceneView::update()
	{
		int32 f = System::FrameCount();
		if (f % 160 == 0) {
			m_bubbleGenerator.add<BubbleEffect>(m_pModel->getCamera().getPos());
		}
	}

	void MainSceneView::draw() const
	{
		const auto& camera = m_pModel->getCamera();
		auto cameraPos = camera.getPos();
		RectF rect = camera.screenRegion();

		// in camera
		{
			auto t2d = camera.getTransformer();
			// BG
			{
				abyss::ScopedRenderStates2D state(YClamp);
				for (const auto& bg : m_pModel->getBgs()) {
					bg.draw(cameraPos);
				}
			}
			m_tiledMap.drawLayer(L"back", rect);
			m_tiledMap.drawLayer(L"map", rect);

			// world;
			m_pModel->getWorld().draw();

			m_tiledMap.drawLayer(L"front", rect);
			// bubble
			{
				abyss::ScopedRenderStates2D state(BlendState::Additive);

				m_bubbleGenerator.update();
			}
		}
	}
}