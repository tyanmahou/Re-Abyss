#include "MainSceneView.h"
#include "../../model/scene/MainSceneModel.hpp"
#include "../../model/MapInfoModel.hpp"
#include "../effects/Bubble.hpp"
#include "../../util/ScopedState.hpp"

#include <Siv3D.hpp>

using namespace s3dTiled;
using namespace abyss;
namespace
{
	// clamp
	constexpr SamplerState YClamp(
		TextureAddressMode::Wrap,
		TextureAddressMode::Clamp,
		TextureAddressMode::Wrap,
		TextureFilter::MinMagMipLinear
	);

	class MapLayerParser
	{
		std::unordered_map<GId, FieldType> m_fieldTypeMap;
		TiledMap m_tiledMap;
		const Grid<GId>& m_grid;

		FieldType getFieldType(GId gId)
		{
			if (gId <= 0) {
				return FieldType::None;
			}
			if (m_fieldTypeMap.find(gId) != m_fieldTypeMap.end()) {
				return m_fieldTypeMap[gId];
			}
			bool isLadder = m_tiledMap.getTileProperty(gId, L"ladder").has_value();
			if (isLadder) {
				return m_fieldTypeMap[gId] = FieldType::Ladder;
			}
			return m_fieldTypeMap[gId] = FieldType::Floor;
		}


		FieldType getFieldType(uint32 x, uint32 y)
		{
			if (x < 0 || x >= m_grid.width) {
				return FieldType::None;
			}
			if (y < 0 || y >= m_grid.height) {
				return FieldType::None;
			}
			return getFieldType(m_grid[y][x]);
		};

		ColDirection calcColDirectrion(uint32 x, uint32 y)
		{
			ColDirection col = collision::None;
			if (getFieldType(x, y - 1) != FieldType::Floor) {
				col = col | collision::Up;
			}

			if (getFieldType(x, y + 1) != FieldType::Floor) {
				col = col | collision::Down;
			}
			if (getFieldType(x - 1, y) != FieldType::Floor) {
				col = col | collision::Left;
			}
			if (getFieldType(x + 1, y) != FieldType::Floor) {
				col = col | collision::Right;
			}
			return col;
		}

		Optional<MapInfoModel> tryToMapInfoModel(uint32 x, uint32 y)
		{
			GId gId = m_grid[y][x];
			if (gId <= 0) {
				return s3d::none;
			}
			MapInfoModel ret;
			ret.type = this->getFieldType(gId);
			auto size = m_tiledMap.getTileSize();
			ret.pos = Vec2{ size.x * x, size.y * y } +static_cast<Vec2>(size) / 2;
			ret.size = m_tiledMap.getTile(gId).size;

			switch (ret.type)
			{
			case FieldType::Floor:
				ret.col = calcColDirectrion(x, y);
				if (ret.col != 0) {
					return ret;
				}
				break;
			case FieldType::Ladder:
				ret.col = collision::None;
				if (getFieldType(x, y - 1) == FieldType::None) {
					ret.col = collision::Up;
				}
				return ret;
			}
			return s3d::none;
		}
	public:
		MapLayerParser(const TiledMap& tiledMap, const Grid<GId>& grid) :
			m_tiledMap(tiledMap),
			m_grid(grid)
		{}

		void forEach(std::function<void(const MapInfoModel&)> callback) {
			for (uint32 y = 0; y < m_grid.height; ++y) {
				for (uint32 x = 0; x < m_grid.width; ++x) {
					if (auto info = this->tryToMapInfoModel(x, y)) {
						callback(*info);
					}
				}
			}
		};
	};
}

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

		// °î•ñ
		m_tiledMap.getLayer(L"map")->then(
			[&](const TileLayer & layer) {
				MapLayerParser(m_tiledMap, layer.getGrid()).forEach(
					[&](const MapInfoModel& info) {
						m_pModel->addMapInfoModel(info);
					}
				);
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

			// Todo current next
			if (!camera.carentRoom().passable(Forward::Down)) {
				RectF(rect.x, rect.y + rect.size.y - 40, rect.w, 40).draw({ColorF(0,0), ColorF(0,0) ,ColorF(0,1),ColorF(0,1)});
			}
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