#include "MainScene.hpp"
#include "../view/effects/Bubble.hpp"
#include "../util/TimeUtil.hpp"
#include "../model/GameCamera.hpp"
#include "../model/Room.hpp"
#include "../model/BgModel.hpp"
#include <S3DTiled.hpp>
#include "../model/PlayerModel.hpp"

using namespace s3dTiled;

namespace abyss
{
	class MainScene::Impl
	{
		TiledMap map;

		PlayerModel m_player;
		GameCamera m_camera;
		Array<Room> m_rooms;
		Array<BgModel> m_bgs;

	
	public:
		Impl() = default;

		Optional<Room> getNextRoom(const Vec2& _pos)
		{
			for (const auto& room : m_rooms) {
				if (room.getRegion().intersects(_pos)) {
					return room;
				}
			}
			return s3d::none;
		}
		void init()
		{
			m_player.setPos({ 480, 720 });
			map.open(L"work/stage0/stage0.tmx");
			map.getLayer(L"room")->then([this](const ObjectGroup & layer) {
				for (const auto& obj : layer.getObjects()) {
					m_rooms.emplace_back(obj);
				}
				});
			m_camera.setRoom(m_rooms[0]);
			m_camera.update(m_player.getPos());

			map.getLayer(L"bgs")->then([&](const GroupLayer & layer) {
				for (const auto& child : layer.getLayers()) {
					child.then([&](const ImageLayer & i) {
						m_bgs.emplace_back(i);
						});
				}
				});
		}

		void update()
		{
			double dt = TimeUtil::Delta();
			m_player.update(dt);
			Vec2 pos = m_player.getPos();
			m_camera.update(pos);
			m_camera.adjustPos(pos);
			m_player.setPos(pos);

			if (!m_camera.isCameraWork() && !m_camera.carentRoom().getRegion().intersects(pos)) {
				if (auto && next = this->getNextRoom(pos)) {
					m_camera.startCameraWork(*next).withPlayerPos(pos);
				}
			}
		}

		void draw() const
		{
			static s3d::Effect e;

			auto cameraPos = m_camera.getPos();
			int32 f = System::FrameCount();
			if (f % 80 == 0) {
				e.add<BubbleEffect>(cameraPos);
				e.setSpeed(0.1);
			}

			constexpr SamplerState YClamp(
				TextureAddressMode::Wrap,
				TextureAddressMode::Clamp,
				TextureAddressMode::Wrap,
				TextureFilter::MinMagMipLinear
			);


			RectF rect = m_camera.screenRegion();
			{
				auto t2d = m_camera.getTransformer();

				Graphics2D::SetSamplerState(YClamp);
				for (const auto& bg : m_bgs) {
					bg.draw(cameraPos);
				}

				Graphics2D::SetSamplerState(SamplerState::Default2D);

				map.drawLayer(L"back", rect);
				map.drawLayer(L"map", rect);

				m_player.draw();

				map.drawLayer(L"front", rect);
				 
				Graphics2D::SetBlendState(BlendState::Additive);
				e.update();
				Graphics2D::SetBlendState(BlendState::Default);
			}

		}
	};
	MainScene::MainScene() :
		m_pImpl(std::make_shared<Impl>())
	{
	}
	void MainScene::init()
	{
		m_pImpl->init();
	}
	void MainScene::update()
	{
		m_pImpl->update();
	}
	void MainScene::draw() const
	{
		m_pImpl->draw();
	}
}