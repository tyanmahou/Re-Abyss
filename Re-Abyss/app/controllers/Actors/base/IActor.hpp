#pragma once
#include "ICollider.hpp"
#include <abyss/models/Actors/base/ComponentsHolder.hpp>
#include <abyss/visitors/ActVisitor.hpp>

namespace abyss
{
	class IActor : public ICollider
	{
	private:
		ComponentsHolder m_components;
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
		inline World* getWorld() const
		{
			return m_pWorld;
		}
		inline void setId(s3d::uint64 id)
		{
			m_id = id;
		}
		inline s3d::uint64 getId() const
		{
			return m_id;
		}
		void setup();
		inline virtual void start() {}
		inline virtual void update(double /*dt*/) {}
		inline virtual void draw()const {}

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

		template<class T, class ... Args>
		std::shared_ptr<T> addComponent(Args&&... args)
		{
			return m_components.add<T>(std::forward<Args>(args)...);
		}

		template<class T>
		std::shared_ptr<T> getComponentRef() const
		{
			return m_components.getRef<T>();
		}
		template<class T>
		T* getComponent() const
		{
			return m_components.get<T>();
		}

		void accept(const ActVisitor& visitor) override;
	};
}