#include "PlayerShotView.hpp"
#include "../../../domain/model/object/PlayerShotModel.hpp"

#include <Siv3D.hpp>

#include <application/common/Constants.hpp>
#include <presentation/view/main/WorldView.hpp>
#include <presentation/view/effects/PlayerShotEffect.hpp>

namespace
{
	using namespace abyss;

	Color TypeToColor(PlayerShotModel::Type type)
	{
		using namespace Constants::Player;
		static const std::unordered_map<PlayerShotModel::Type, Color> colorMap{
			{PlayerShotModel::Type::Normal, ColorF(1)},
			{PlayerShotModel::Type::Small, ColorF(1)},
			{PlayerShotModel::Type::Medium, MediumChargeColorBase},
			{PlayerShotModel::Type::Big, BigChargeColorBase},
		};
		return colorMap.at(type);
	}
}
namespace abyss
{
	PlayerShotView::PlayerShotView(std::shared_ptr<PlayerShotModel> pModel) :
		m_texture(U"work/player/player_shot.png"),
		m_pModel(pModel)
	{

	}

	void PlayerShotView::start()
	{
		auto pModel = m_pModel.lock();
		if (!pModel) {
			return;
		}
		auto  type = pModel->getType();
		auto r = pModel->getColliderCircle().r;
		auto pos = pModel->getPos();

		// effect
		if (type != PlayerShotModel::Type::Normal) {
			m_pWorldView->getEffect().add<PlayerShotFiringEffect>(pos, r, ::TypeToColor(type));
		}
	}

	void PlayerShotView::update()
	{
		auto pModel = m_pModel.lock();
		if (!pModel) {
			return;
		}
		auto  type = pModel->getType();
		auto r = pModel->getColliderCircle().r;
		auto pos = pModel->getPos();

		// effect
		if (Scene::FrameCount() % 2 && (type == PlayerShotModel::Type::Big || type == PlayerShotModel::Type::Medium)) {
			m_pWorldView->getEffect().add<PlayerShotEffect>(pos, r, ::TypeToColor(type));
		}
	}

	void PlayerShotView::draw() const
	{
		using Type = PlayerShotModel::Type;
		auto model = m_pModel.lock();

		auto type = model->getType();

		double x = 0, y = 0;
		double size = 0;
		double timer = Periodic::Sawtooth0_1(0.3s);
		if (type == Type::Normal) {
			y = 10 * static_cast<int>(timer * 2);
			size = 10;
		}
		else if (type == Type::Small) {
			x = 10;
			y = 20 * static_cast<int>(timer * 2);
			size = 20;
		}
		else if (type == Type::Medium) {
			x = 30 + 40 * static_cast<int>(timer * 4);
			size = 40;
		}
		else {
			x = 60 * static_cast<int>(timer * 4);
			y = 40;
			size = 60;
		}
		auto tile = m_texture(x, y, size, size);
		(model->getForward() == Forward::Right ? tile : tile.mirrored()).drawAt(model->getPos());
	}

	bool PlayerShotView::isDelete() const
	{
		return m_pModel.expired();
	}

}
