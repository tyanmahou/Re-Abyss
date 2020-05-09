#include "Senser.hpp"

#include <abyss/models/Actors/Slime/Sencer/MainUpdateModel.hpp>
#include <abyss/models/Actors/Slime/Sencer/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Slime/Sencer/CollisionModel.hpp>
#include <abyss/models/Actors/Commons/PosModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

namespace abyss::Slime
{
	Senser::Senser(SlimeActor* p)
	{
		m_pos = this->addComponent<PosModel>();
		this->addComponent<Sencer::MainUpdateModel>(this);
		this->addComponent<Sencer::ParentCtrlModel>(p);
		this->addComponent<Sencer::CollisionModel>();

		this->addComponent<CustomColliderModel>(this)
			->setColFunc([this]() {
			return this->getPos();
		});
	}
	const s3d::Vec2& Senser::getPos() const
	{
		return m_pos->getPos();
	}
}
