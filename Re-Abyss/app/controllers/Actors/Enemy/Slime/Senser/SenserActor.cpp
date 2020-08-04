#include "SenserActor.hpp"

#include <abyss/models/Actors/Enemy/Slime/Sencer/MainUpdateModel.hpp>
#include <abyss/models/Actors/Enemy/Slime/Sencer/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>

namespace abyss::Slime
{
	SenserActor::SenserActor(SlimeActor* p)
	{
		m_body = this->attach<BodyModel>(this);
		this->attach<Sencer::MainUpdateModel>(this);
		this->attach<Sencer::ParentCtrlModel>(p);

		this->attach<MapColliderModel>(this)->setIsThrough(true);
	}
	const s3d::Vec2& SenserActor::getPos() const
	{
		return m_body->getPos();
	}
}
