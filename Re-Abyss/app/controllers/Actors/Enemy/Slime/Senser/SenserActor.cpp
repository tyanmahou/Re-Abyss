#include "SenserActor.hpp"

#include <abyss/components/Actors/Enemy/Slime/Sencer/MainUpdate.hpp>
#include <abyss/components/Actors/Enemy/Slime/Sencer/ParentCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>

namespace abyss::Actor::Enemy::Slime
{
	SenserActor::SenserActor(SlimeActor* p)
	{
		m_body = this->attach<Body>(this);
		this->attach<Sencer::MainUpdate>(this);
		this->attach<Sencer::ParentCtrl>(p);

		this->attach<MapCollider>(this)->setIsThrough(true);
	}
	const s3d::Vec2& SenserActor::getPos() const
	{
		return m_body->getPos();
	}
}
