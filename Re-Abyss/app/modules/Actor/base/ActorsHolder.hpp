#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Actor
{
	class ActorsHolder
	{
		s3d::Array<std::shared_ptr<ActorObj>> m_reserves;
		s3d::Array<std::shared_ptr<ActorObj>> m_actors;

		s3d::uint64 m_objIdCounter = 0;
	public:
		void flush();
		void pushActor(const std::shared_ptr<ActorObj>& obj);
		void updateDeltaTime(double dt);

		void preUpdate();
		void update();
		void postUpdate();

		void move() const;

		void prePhysics() const;

		void postPhysics() const;

		void preCollision() const;
		void postCollision() const;

		void lastUpdate();
		void draw()const;

		void erase();

		void onCheckIn(BufferLayer layer);

		void onCheckOut(BufferLayer layer);

		void clear();

		void clear(DestoryTiming timing, BufferLayer layer);

		s3d::Array<std::shared_ptr<ActorObj>>& getActors();
		const s3d::Array<std::shared_ptr<ActorObj>>& getActors() const;

		template<class Type>
		[[nodiscard]] Ref<Type> find() const
		{
			for (const auto& actor : m_actors) {
				if(auto&& c = actor->find<Type>()) {
					return c;
				}
			}
			return nullptr;
		}
		template<class Type>
		[[nodiscard]] Ref<ActorObj> findActor() const
		{
			for (const auto& actor : m_actors) {
				if (auto&& c = actor->find<Type>()) {
					return actor;
				}
			}
			return nullptr;
		}
		template<class Type>
		[[nodiscard]] s3d::Array<Ref<Type>> finds() const
		{
			s3d::Array<Ref<Type>> ret;
			for (const auto& actor : m_actors) {
				for (auto&& c : actor->finds<Type>()) {
					ret.push_back(c);
				}
			}
			return ret;
		}
	};
}
