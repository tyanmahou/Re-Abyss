#pragma once
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/components/base/Components.hpp>
#include <Siv3D/Duration.hpp>
#include <Siv3D/ISteadyClock.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/modules/Actor/base/Tag.hpp>
#include <abyss/modules/Actor/base/BufferLayer.hpp>
#include <abyss/modules/Actor/base/DestroyTiming.hpp>

namespace abyss::Actor
{
	class ActorObj final : public GameObject
	{
	private:
		Ref<ClockCtrl> m_clock;
		s3d::uint64 m_id;
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

		void setTag(const TagType& tag);
		const TagType& getTag() const;

		void setBufferLayer(BufferLayer layer);

		BufferLayer getBufferLayer()const;

		void updateDeltaTime(double worldDt) const;

		void preUpdate();
		void update();
		void postUpdate();

		void move();

		void prePhysics();
		void postPhysics();

		void preCollision();
		void postCollision();

		void lastUpdate();
		void draw()const;

		s3d::Microseconds getTime() const;
		double getTimeSec() const;
		s3d::ISteadyClock* getClock() const;

		double deltaTime() const;

		template<TaggedOf<Tag::ActorTagKind> T>
		bool isThen(std::function<bool(ActorObj*)> callback);

		template<TaggedOf<Tag::ActorTagKind> T, IsComponent C>
		bool isThen(std::function<bool(C&)> callback) const;

		template<TaggedOf<Tag::ActorTagKind> T>
		bool isNotThen(std::function<bool(ActorObj*)> callback);
	};
}
#include "ActorObj.ipp"