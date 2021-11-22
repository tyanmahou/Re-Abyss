#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/utils/IdGenerator/IdGen.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Collision
{
	class IDetectionAlgorithm;
	class Branch;

	class CollisionManager
	{
	public:
		CollisionManager();

		s3d::uint64 createId();

		Ref<Branch> add(s3d::uint64 id);

		void onCollision();
		void cleanUp();
	private:
		std::shared_ptr<IDetectionAlgorithm> m_detection;
		s3d::Array<std::shared_ptr<Branch>> m_branchs;
		IdGenU64 m_idCounter;
	};
}