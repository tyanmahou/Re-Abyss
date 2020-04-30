#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::EventTrigger
{
	class EventTriggerActor : public IActor
	{
	private:
		s3d::FilePath m_path;
	public:
		EventTriggerActor(const s3d::FilePath& path);
		
		void start()override;
		CShape getCollider() const override;
		bool accept(const ActVisitor& visitor) override;
	};
}