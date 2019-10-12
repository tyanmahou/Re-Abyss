#pragma once
#include <memory>
#include <domain/actor/IActor.hpp>
#include <domain/model/WorldModel.hpp>
#include <presentation/view/main/WorldView.hpp>

namespace abyss
{
	template<class Type>
	concept IsActor = std::is_base_of_v<IActor, Type>;

	class ICollisionUseCase;
	class IWorldView;

	class WorldFacade
	{
	private:
		WorldModel m_worldModel;
		std::unique_ptr<ICollisionUseCase> m_collisionUseCase;
		WorldView m_worldView;
	public:
		WorldFacade() = default;

		WorldFacade(std::unique_ptr<ICollisionUseCase>&& collision);

		void update();
		void draw()const;

		template<IsActor Type, class... Args>
		void create(Args&& ... args)
		{
			auto obj = std::make_shared<Type>(std::forward<Args>(args)...);
			this->regist(obj);
		}

		template<IsActor Type>
		void regist(const std::shared_ptr<Type>& object)
		{
			m_worldModel.pushActor(object);
		}
	};

	using World = WorldFacade;
}