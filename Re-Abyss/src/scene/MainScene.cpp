#include "MainScene.hpp"
#include "../view/effects/Bubble.hpp"
#include "../util/TimeUtil.hpp"
#include "../model/GameCamera.hpp"
#include "../model/Room.hpp"
#include <S3DTiled.hpp>

using namespace s3dTiled;

namespace abyss
{
	class MainScene::Impl
	{
		TiledMap map;

		Vec2 pos;
		GameCamera m_camera;
		Array<Room> m_rooms;

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
			pos = {480, 260};
			map.open(L"work/stage0/stage0.tmx");
			map.getLayer(L"room")->then([this](const ObjectGroup& layer) {
				for (const auto& obj : layer.getObjects()) {
					m_rooms.emplace_back(obj);
				}
			});
			m_camera.setRoom(m_rooms[0]);
			m_camera.update(pos);
		}

		void update()
		{
			pos.x += (Input::KeyRight.pressed - Input::KeyLeft.pressed) * 200 * TimeUtil::Delta();
			pos.y += (Input::KeyDown.pressed - Input::KeyUp.pressed) * 200 * TimeUtil::Delta();

			m_camera.update(pos);
			m_camera.adjustPos(pos);

			if (!m_camera.isCameraWork() && !m_camera.carentRoom().getRegion().intersects(pos)) {
				if (auto && next = this->getNextRoom(pos)) {
					m_camera.startCameraWork(*next).withPlayerPos(pos);
				}
			}
		}

		void draw() const
		{
			static s3d::Effect e;
			static Texture tex(L"resources/Images/bgs/stage0-4.png");
			static Texture tex2(L"resources/Images/bgs/stage0-3.png");
			static Texture tex3(L"resources/Images/bgs/stage0-2.png");
			static Texture tex4(L"resources/Images/bgs/stage0-1.png");


			int32 f = System::FrameCount();
			if (f % 80 == 0) {
				e.add<BubbleEffect>(m_camera.getPos());
				e.setSpeed(0.1);
			}
			tex.draw(Vec2{ 0, 20 });

			tex2.uv(m_camera.getPos().x / 960 / 3, 0, 1, 1).draw(Vec2{ 0, 20 });
			tex3.uv(m_camera.getPos().x / 960 / 2, 0, 1, 1).draw(Vec2{ 0, 20 });
			tex4.uv(m_camera.getPos().x / 960, 0, 1, 1).draw(Vec2{ 0, 20 });

			RectF rect = m_camera.screenRegion();

			{
				auto t2d = m_camera.getTransformer();

				map.drawLayer(L"back", rect);
				map.drawLayer(L"map", rect);
				Circle(pos, 20).draw(Palette::Red);
				map.drawLayer(L"front", rect);
				// 
				Graphics2D::SetBlendState(BlendState::Additive);
				e.update();
				Graphics2D::SetBlendState(BlendState::Default);
			}

		}
	};
	MainScene::MainScene():
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