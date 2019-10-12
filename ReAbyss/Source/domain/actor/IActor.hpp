#pragma once
#include "ICollider.hpp"
#include <domain/visitor/ActVisitor.hpp>
#include <presentation/view/actor/IActorView.hpp>

namespace abyss
{
	class World;
	class ActVisitor;

	class IActor : public ICollider
	{
	private:
		std::unique_ptr<IActorView> m_view;
	protected:
		World* m_pWorld = nullptr;
		s3d::uint64 m_id;
		bool m_isActive = true;

	public:
		IActor() = default;
		virtual ~IActor() = default;

		inline void setWorld(World* const pWorld)
		{
			m_pWorld = pWorld;
		}
		inline void setId(s3d::uint64 id)
		{
			m_id = id;
		}
		inline s3d::uint64 getId() const
		{
			return m_id;
		}
		inline virtual void start() {}
		inline virtual void update(double /*dt*/) {}
		inline virtual void draw()const {
			if (m_view) {
				m_view->draw();
			}
		}
		inline void setActive(bool active)
		{
			m_isActive = active;
		}
		inline void destroy()
		{
			this->setActive(false);
		}
		inline bool isDelete() const
		{
			return !m_isActive;
		}

		void accept(const ActVisitor& visitor) override;

		inline virtual std::unique_ptr<IActorView> createView()const { return nullptr; }

		void initView();
	};
}