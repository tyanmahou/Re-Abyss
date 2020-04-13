#pragma once
#include "ICollider.hpp"
#include <abyss/visitors/ActVisitor.hpp>
#include <abyss/controllers/ActionSystem/ActManager.hpp>

namespace abyss
{
	class IActor : public ICollider
	{
	protected:
		ActManager* m_pManager = nullptr;
		s3d::uint64 m_id;
		bool m_isActive = true;
		bool m_isDontDestoryOnLoad = false;
	public:
		IActor() = default;
		virtual ~IActor() = default;

		inline void setManager(ActManager* const pManager)
		{
			m_pManager = pManager;
		}
		inline ActManager* getManager() const
		{
			return m_pManager;
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
		inline virtual void update([[maybe_unused]]double dt) {}
		inline virtual void lastUpdate([[maybe_unused]] double dt) {}
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

		inline bool isDontDestoryOnLoad() const
		{
			return m_isDontDestoryOnLoad;
		}
		bool accept(const ActVisitor& visitor) override;

		template<class T>
		T* getModule() const
		{
			if (!m_pManager) {
				return nullptr;
			}
			return m_pManager->getModule<T>();
		}
	};
}