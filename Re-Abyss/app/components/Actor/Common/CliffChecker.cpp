#include <abyss/components/Actor/Common/CliffChecker.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Physics/PhysicsManager.hpp>
#include <abyss/modules/Physics/base/IContacter.hpp>
#include <abyss/modules/Physics/base/TerrainData.hpp>

#include <abyss/components/Actor/Common/Body.hpp>

#include <Siv3D.hpp>

namespace
{
	using namespace abyss;
	using namespace abyss::Actor;

	class Contacter : public Physics::IContacter
	{
	public:
		Contacter(ActorObj* pActor) :
			m_pActor(pActor)
		{}

		void setId(s3d::uint64 id) override
		{
			m_id = id;
		}
		s3d::uint64 id() const override
		{
			return m_id;
		}

		bool isActive() const override
		{
			return !m_isDestroyed && m_pActor->isActive();
		}

		void destroy()
		{
			m_isDestroyed = true;
		}

		bool isDestroyed() const override
		{
			return m_isDestroyed;
		}

		const CShape& getShape() const override
		{
			return m_shape;
		}
		void onPrePhysics(const Vec2& pos)
		{
			m_isHitAny = false;
			m_shape = pos;
		}
		void onCollision(const Physics::TerrainData&) override
		{
			m_isHitAny = true;
		}

		bool isHitAny() const
		{
			return m_isHitAny;
		}
	private:
		ActorObj* m_pActor;
		bool m_isDestroyed = false;
		s3d::uint64 m_id = 0;
		CShape m_shape;
		bool m_isHitAny = true;
	};
}
namespace abyss::Actor
{
	class CliffChecker::Impl
	{
	public:
		Impl(ActorObj* pActor):
			m_pActor(pActor),
			m_front(std::make_shared<Contacter>(pActor)),
			m_back(std::make_shared<Contacter>(pActor))
		{}

		void setFrontOffset(const Vec2& offset)
		{
			m_frontOffset = offset;
		}
		void setBackOffset(const s3d::Vec2& offset)
		{
			m_backOffset = offset;
		}
		void onStart()
		{
			m_body = m_pActor->find<Body>();

			m_pActor->getModule<PhysicsManager>()->regist(m_front);
			m_pActor->getModule<PhysicsManager>()->regist(m_back);
		}
		void onEnd()
		{
			m_front->destroy();
			m_back->destroy();
		}
		void onPrePhysics()
		{
			auto footPos = m_body->region().bottomCenter();
			const Vec2& front = m_frontOffset;
			const Vec2 frontRev = Vec2{ -front.x, front.y };

			const Vec2 back = m_backOffset.value_or(frontRev);
			const Vec2 backRev = Vec2{-back.x, back.y};

			if (m_body->isForward(Forward::Left())) {
				m_front->onPrePhysics(footPos + front);
				m_back->onPrePhysics(footPos + back);
			} else {
				m_front->onPrePhysics(footPos + frontRev);
				m_back->onPrePhysics(footPos + backRev);
			}
		}
		bool isCliff() const
		{
			return !m_front->isHitAny();
		}
		bool isCliffBack() const
		{
			return !m_back->isHitAny();
		}
		bool isCliffAround() const
		{
			return !m_front->isHitAny() && !m_back->isHitAny();
		}
		bool isCliffForwardOnly() const
		{
			return !m_front->isHitAny() && m_back->isHitAny();
		}
	private:
		ActorObj* m_pActor;
		Ref<Body> m_body;
		Vec2 m_frontOffset{};
		Optional<Vec2> m_backOffset;
		std::shared_ptr<Contacter> m_front;
		std::shared_ptr<Contacter> m_back;
	};
	CliffChecker::CliffChecker(ActorObj* pActor):
		m_pImpl(std::make_unique<Impl>(pActor))
	{}
	CliffChecker::~CliffChecker()
	{}
	CliffChecker& CliffChecker::setFrontOffset(const s3d::Vec2 & offset)
	{
		m_pImpl->setFrontOffset(offset);
		return *this;
	}
	CliffChecker& CliffChecker::setBackOffset(const s3d::Vec2& offset)
	{
		m_pImpl->setBackOffset(offset);
		return *this;
	}
	void CliffChecker::onStart()
	{
		m_pImpl->onStart();
	}
	void CliffChecker::onEnd()
	{
		m_pImpl->onEnd();
	}
	void CliffChecker::onPrePhysics()
	{
		m_pImpl->onPrePhysics();
	}
	bool CliffChecker::isCliff() const
	{
		return m_pImpl->isCliff();
	}
	bool CliffChecker::isCliffBack() const
	{
		return m_pImpl->isCliffBack();
	}
	bool CliffChecker::isCliffAround() const
	{
		return m_pImpl->isCliffAround();
	}
	bool CliffChecker::isCliffForwardOnly() const
	{
		return m_pImpl->isCliffForwardOnly();
	}
}
