#pragma once
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/components/base/Components.hpp>
#include <Siv3D/Duration.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/modules/Actors/base/Tag.hpp>

namespace abyss::Actor
{
	class IActor final : public GameObject
	{
	private:
		Ref<Actor::ActorTime> m_time;
		s3d::uint64 m_id;
		s3d::int32 m_order = 0;
		bool m_isDontDestoryOnLoad = false;

		TagType m_tag;
	public:
		IActor();
		~IActor() = default;

		void setId(s3d::uint64 id);
		s3d::uint64 getId() const;
		
		void setIsDontDestoryOnLoad(bool isDontDestoryOnLoad = true);
		bool isDontDestoryOnLoad() const;

		void setOrder(s3d::int32 order);
		s3d::int32 getOrder() const;

		void setTag(const TagType& tag);
		const TagType& getTag() const;

		void updateDeltaTime(double worldDt) const;

		void update();
		void move();
		void prePhysics();

		void lastPhysics();

		void preCollision();
		void collisionReact();

		void lastUpdate();
		void draw()const;

		s3d::Microseconds getUpdateTime() const;
		double getUpdateTimeSec() const;
		std::function<s3d::Microseconds()> getUpdateTimer() const;

		s3d::Microseconds getDrawTime() const;
		double getDrawTimeSec() const;
		std::function<s3d::Microseconds()> getDrawTimer() const;

		double deltaTime() const;

		template<Tag::Tagged T>
		bool isThen(std::function<bool(IActor*)> callback);

		template<Tag::Tagged T, IsComponent C>
		bool isThen(std::function<bool(C&)> callback) const;

		template<Tag::Tagged T>
		bool isNotThen(std::function<bool(IActor*)> callback);
	};
}
#include "IActor.ipp"