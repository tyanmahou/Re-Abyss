#pragma once
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/components/base/Components.hpp>
#include <Siv3D/Duration.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/modules/Actor/base/Tag.hpp>
#include <abyss/modules/Actor/base/BufferLayer.hpp>
#include <abyss/modules/Actor/base/DestroyTiming.hpp>

namespace abyss::Actor
{
	class ActorObj final : public GameObject
	{
	private:
		Ref<Actor::ClockCtrl> m_clock;
		s3d::uint64 m_id;
		s3d::int32 m_order = 0;
		DestoryTiming m_destoryTiming = DestoryTiming::Default;

		TagType m_tag;
		BufferLayer m_bufferLayer;
	public:
		ActorObj();
		~ActorObj() = default;

		void setId(s3d::uint64 id);
		s3d::uint64 getId() const;
		
		void setDestoryTiming(DestoryTiming timing);
		DestoryTiming getDestoryTiming() const;
		bool isDestoryCheckIn() const;
		bool isDestoryCheckOut() const;
		bool isDestoryNever() const;

		void setOrder(s3d::int32 order);
		s3d::int32 getOrder() const;

		void setTag(const TagType& tag);
		const TagType& getTag() const;

		void setBufferLayer(BufferLayer layer);

		BufferLayer getBufferLayer()const;

		void updateDeltaTime(double worldDt) const;

		void update();
		void postUpdate();

		void move();

		void prePhysics();
		void postPhysics();

		void preCollision();
		void postCollision();

		void lastUpdate();
		void draw()const;

		s3d::Microseconds getUpdateTime() const;
		double getUpdateTimeSec() const;
		std::function<s3d::Microseconds()> getUpdateClock() const;

		s3d::Microseconds getDrawTime() const;
		double getDrawTimeSec() const;
		std::function<s3d::Microseconds()> getDrawClock() const;

		double deltaTime() const;

		template<Tag::Tagged T>
		bool isThen(std::function<bool(ActorObj*)> callback);

		template<Tag::Tagged T, IsComponent C>
		bool isThen(std::function<bool(C&)> callback) const;

		template<Tag::Tagged T>
		bool isNotThen(std::function<bool(ActorObj*)> callback);
	};
}
#include "ActorObj.ipp"