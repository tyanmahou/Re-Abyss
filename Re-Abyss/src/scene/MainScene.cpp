#include "MainScene.hpp"

#include "../model/scene/MainSceneModel.hpp"
#include "../view/scene/MainSceneView.h"

namespace abyss
{
	enum class FieldType
	{
		None = 0x0,
		Floor = 0x1,
		Ladder = 0x2,
	};

	class MainScene::Controller
	{
		std::unique_ptr<MainSceneModel> m_model;
		std::unique_ptr<MainSceneView> m_view;
	public:
		Controller() :
			m_model(std::make_unique<MainSceneModel>()),
			m_view(std::make_unique<MainSceneView>(m_model.get()))
		{
		
		}


		void init()
		{
			m_model->init();
			//map.getLayer(L"map")->then([&](const TileLayer & layer) {
			//	const auto& grid = layer.getGrid();
			//	auto size = map.getTileSize();

			//	std::unordered_map<GId, FieldType> fieldTypeMap;
			//	auto getFieldType = [&](GId gId)-> FieldType {
			//		if (gId <= 0) {
			//			return FieldType::None;
			//		}
			//		if (fieldTypeMap.find(gId) != fieldTypeMap.end()) {
			//			return fieldTypeMap[gId];
			//		}
			//		bool isLadder = map.getTileProperty(gId, L"ladder").has_value();
			//		if (isLadder) {
			//			return fieldTypeMap[gId] = FieldType::Ladder;
			//		}
			//		return fieldTypeMap[gId] = FieldType::Floor;
			//	};

			//	auto getMapType = [&](uint32 x, uint32 y) {
			//		if (x < 0 || x >= grid.width) {
			//			return FieldType::None;
			//		}
			//		if (y < 0 || y >= grid.height) {
			//			return FieldType::None;
			//		}
			//		return getFieldType(grid[y][x]);
			//	};

			//	for (uint32 y = 0; y < grid.height; ++y) {
			//		for (uint32 x = 0; x < grid.width; ++x) {
			//			GId gId = grid[y][x];
			//			if (gId <= 0) {
			//				continue;
			//			}
			//			auto type = getFieldType(gId);
			//			if (type != FieldType::Floor) {
			//				continue;
			//			}
			//			ColDirection col = collision::None;

			//			if (getMapType(x, y - 1) != FieldType::Floor) {
			//				col = col | collision::Up;
			//			}

			//			if (getMapType(x, y + 1) != FieldType::Floor) {
			//				col = col | collision::Down;
			//			}
			//			if (getMapType(x - 1, y) != FieldType::Floor) {
			//				col = col | collision::Left;
			//			}
			//			if (getMapType(x + 1, y) != FieldType::Floor) {
			//				col = col | collision::Right;
			//			}

			//			Vec2 pos = Vec2{ size.x * x, size.y * y } +static_cast<Vec2>(size) / 2;
			//			world.createObject<FloorModel>(col, pos, map.getTile(gId).size);
			//		}
			//	}
			//	});
		}

		void update()
		{
			m_model->update();
			m_view->update();
		}

		void draw() const
		{
			m_view->draw();
		}
	};
	MainScene::MainScene() :
		m_pImpl(std::make_unique<Controller>())
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