#pragma once
#include <abyss/visitors/ActVisitor.hpp>
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/models/Actors/base/Components.hpp>

namespace abyss
{
	class IActor
	{
	private:
		bool m_isDestroyed = false;
		Components m_components;
		Ref<ActorTimeModel> m_time;
	protected:
		Manager* m_pManager = nullptr;
		s3d::uint64 m_id;
		bool m_isActive = true;
		bool m_isDontDestoryOnLoad = false;
		s3d::int32 m_order = 0;
		
	public:
		IActor();
		virtual ~IActor() = default;

		void setManager(Manager* const pManager);
		Manager* getManager() const;

		void setId(s3d::uint64 id);
		s3d::uint64 getId() const;

		void setActive(bool active);
		bool isActive() const;

		void destroy();
		bool isDestroyed() const;
		bool isDontDestoryOnLoad() const;

		s3d::int32 getOrder() const;

		void updateDeltaTime(double worldDt) const;
		void setup() const;
		virtual void start() {}
		void update();
		void move();
		void prePhysics();

		void lastPhysics();

		void lastUpdate();
		void draw()const;

		virtual bool accept(const ActVisitor& visitor);

		template<class T>
		T* getModule() const;

		s3d::Microseconds getUpdateTime() const;
		double getUpdateTimeSec() const;
		std::function<s3d::Microseconds()> getUpdateTimer() const;

		s3d::Microseconds getDrawTime() const;
		double getDrawTimeSec() const;
		std::function<s3d::Microseconds()> getDrawTimer() const;

		/// <summary>
		/// コンポーネントを付与
		/// </summary>
		template<class Component>
		Ref<Component> attach(const std::shared_ptr<Component>& component) const
			requires IsComponent<Component>
		;

		/// <summary>
		/// コンポーネントを構築して付与
		/// </summary>
		template<class Component, class... Args>
		Ref<Component> attach(Args&&... args) const
			requires
			IsComponent<Component>&&
			std::constructible_from<Component, Args...>
		;

		/// <summary>
		/// コンポーネントを取り除きます
		/// </summary>
		template<class Component>
		bool detach() const
			requires IsComponent<Component>
		;

		template<class Component>
		[[nodiscard]] Ref<Component> find() const;

		template<class Component>
		[[nodiscard]] s3d::Array<Ref<Component>> finds() const;

	};
}
#include "IActor.ipp"