#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Enemy::Slime
{
	class SlimeActor;

    class SenserActor : public IActor
    {
		Ref<BodyModel> m_body;
	public:
		SenserActor(SlimeActor* p);

		const s3d::Vec2& getPos() const;
    };
}