#include "PlayerShotView.hpp"
#include "../../../domain/model/object/PlayerShotModel.hpp"
#include "../../../application/util/Periodic.hpp"
#include <Siv3D.hpp>

namespace abyss
{
	PlayerShotView::PlayerShotView(std::shared_ptr<PlayerShotModel> pModel) :
		m_texture(L"work/player/player_shot.png"),
		m_pModel(pModel)
	{}

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
		(model->getForward() == Forward::Right ? tile : tile.mirror()).drawAt(model->getPos());
	}

	bool PlayerShotView::isDelete() const
	{
		return m_pModel.expired();
	}

}
