#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/utils/IdGenerator/IdGen.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Collision
{
	class IDetectionAlgorithm;
	class INode;

	class CollisionManager
	{
	public:
		CollisionManager();

		void onCollision();
		void cleanUp();
	private:
		std::shared_ptr<IDetectionAlgorithm> m_detection;
		s3d::Array<std::shared_ptr<INode>> m_nodes;
		IdGenU64 m_idCounter;
	};
}