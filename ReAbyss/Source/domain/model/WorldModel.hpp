#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/Fwd.hpp>

#include <memory>
namespace abyss
{
	class WorldObject;

	class WorldModel
	{
		s3d::Array<std::shared_ptr<WorldObject>> m_reserves;
		s3d::Array<std::shared_ptr<WorldObject>> m_objects;

		s3d::uint64 m_objIdCounter = 0;
	public:
		void pushObject(const std::shared_ptr<WorldObject>& obj);
		
		void update();
		void draw()const;

		void erase();

		void clear();

		s3d::Array<std::shared_ptr<WorldObject>>& getObjects();
		const s3d::Array<std::shared_ptr<WorldObject>>& getObjects() const;
	};
}