#pragma once
#include <memory>

#include <Siv3D/Array.hpp>
#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/Actor.hpp>
#include <abyss/concepts/Component.hpp>

namespace abyss
{
	class ActorsHolder
	{
		s3d::Array<std::shared_ptr<IActor>> m_reserves;
		s3d::Array<std::shared_ptr<IActor>> m_actors;

		s3d::uint64 m_objIdCounter = 0;
	public:
		void flush();
		void pushActor(const std::shared_ptr<IActor>& obj);
		void updateDeltaTime(double dt);
		void update();

		void prePhysics() const;

		void lastPhysics() const;

		void lastUpdate();
		void draw()const;

		void erase();

		void clear();

		s3d::Array<std::shared_ptr<IActor>>& getActors();
		const s3d::Array<std::shared_ptr<IActor>>& getActors() const;

		template<class Type>
		[[nodiscard]] Ref<Type> find() const
			requires IsActor<Type>
		{
			for (const auto& actor : m_actors) {
				if (dynamic_cast<Type*>(actor.get())) {
					return std::dynamic_pointer_cast<Type>(actor);
				}
			}
			return nullptr;
		}

		template<class Type>
		[[nodiscard]] s3d::Array<Ref<Type>> finds() const
		{
			s3d::Array<Ref<Type>> ret;
			for (const auto& actor : m_actors) {
				if (auto c = actor->find<Type>()) {
					ret.push_back(c);
				}
			}
			return ret;
		}
	};
}
