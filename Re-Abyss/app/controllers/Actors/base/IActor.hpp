#pragma once
#include "ICollider.hpp"
#include <abyss/visitors/ActVisitor.hpp>
#include <abyss/controllers/ActionSystem/ActManager.hpp>
#include <abyss/models/Actors/base/Components.hpp>

namespace abyss
{
	class IActor : public ICollider
	{
	private:
		bool m_isDestroyed = false;
		Components m_components;
		Ref<ActorTimeModel> m_time;
	protected:
		ActManager* m_pManager = nullptr;
		s3d::uint64 m_id;
		bool m_isActive = true;
		bool m_isDontDestoryOnLoad = false;
		s3d::int32 m_order = 0;
		
		virtual void update([[maybe_unused]] double dt) {}
		virtual void lastUpdate([[maybe_unused]] double dt) {}
	public:
		IActor();
		virtual ~IActor() = default;

		void setManager(ActManager* const pManager);
		ActManager* getManager() const;

		void setId(s3d::uint64 id);
		s3d::uint64 getId() const;

		void setActive(bool active);
		bool isActive() const;

		void destroy();
		bool isDestroyed() const;
		bool isDontDestoryOnLoad() const;

		s3d::int32 getOrder() const;

		void updateTime(double worldDt) const;
		void setup() const;
		virtual void start() {}
		void update();
		void lastUpdate();
		virtual void draw()const {}

		bool accept(const ActVisitor& visitor) override;

		template<class T>
		T* getModule() const;

		template<class Component>
		Ref<Component> addComponent(const std::shared_ptr<Component>& component)
			requires IsComponent<Component>
		;

		template<class Component, class... Args>
		Ref<Component> addComponent(Args&&... args)
			requires
			IsComponent<Component>&&
			std::constructible_from<Component, Args...>
		;

		template<class Component>
		[[nodiscard]] Ref<Component> findComponent() const
			requires IsComponent<Component>
		;

		template<class Component>
		[[nodiscard]] s3d::Array<Ref<Component>> findComponents() const
			requires IsComponent<Component>
		;
	};
}
#include "IActor.ipp"