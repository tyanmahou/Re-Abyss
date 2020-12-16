#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
	class EventTriggerActor : public IActor
	{
	public:
		EventTriggerActor(const s3d::FilePath& path);
	};
}