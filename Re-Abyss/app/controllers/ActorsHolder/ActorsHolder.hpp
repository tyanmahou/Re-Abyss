#pragma once
#include <memory>

#include <Siv3D/Array.hpp>
#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class ActorsHolder
	{
		s3d::Array<std::shared_ptr<IActor>> m_reserves;
		s3d::Array<std::shared_ptr<IActor>> m_actors;

		s3d::uint64 m_objIdCounter = 0;
	public:
		void pushActor(const std::shared_ptr<IActor>& obj);

		void update();
		void draw()const;

		void erase();

		void clear();

		s3d::Array<std::shared_ptr<IActor>>& getActors();
		const s3d::Array<std::shared_ptr<IActor>>& getActors() const;
	};
}
