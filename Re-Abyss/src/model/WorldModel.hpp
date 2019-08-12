#pragma once

#include "WorldObject.hpp"
#include <Siv3D/Array.hpp>
#include <type_traits>
#include <memory>

namespace abyss
{
	class PlayerModel;
	class WorldModel
	{
		PlayerModel* m_playerModel = nullptr;

		s3d::Array<std::shared_ptr<WorldObject>> m_reserves;
		s3d::Array<std::shared_ptr<WorldObject>> m_objects;
	public:
		template<class T, class... Args>
		void createObject(Args&& ... args)
		{
			auto obj = std::make_shared<T>(std::forward<Args>(args)...);
			obj->setWorld(this);
			m_reserves.push_back(std::move(obj));
		}

		void registerObject(const std::shared_ptr<WorldObject>& obj);

		void registerObject(const std::shared_ptr<PlayerModel>& obj);

		void update();

		void draw()const;
	};
}