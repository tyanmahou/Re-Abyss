#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::EventTrigger
{
	class EventTriggerActor : public IActor
	{
	public:
		EventTriggerActor(const s3d::FilePath& path);
		bool accept(const ActVisitor& visitor) override;
	};
}