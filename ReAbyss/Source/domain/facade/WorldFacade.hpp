#pragma once
#include <memory>
#include <domain/actor/IActor.hpp>
#include <domain/model/WorldModel.hpp>
#include <presentation/view/main/WorldView.hpp>
#include <domain/model/CameraModel.hpp>

namespace abyss
{
	template<class Type>
	concept IsActor = std::is_base_of_v<IActor, Type>;

	class PlayerActor;

	class ICollisionUseCase;
	class IWorldView;

	class World
	{
	private:
		WorldModel m_worldModel;
		std::unique_ptr<ICollisionUseCase> m_collisionUseCase;
		WorldView m_worldView;
	public:
		World() = default;

		World(std::unique_ptr<ICollisionUseCase>&& collision);

		void update();
		void draw()const;

		PlayerActor* getPlayer()const { return nullptr; }
		CameraModel* getCamera()const { return nullptr; }

		template<class Type, class... Args>
		void addEffect(Args&& ... args)
		{
			m_worldView.getEffect().add<Type>(std::forward<Args>(args)...);
		}

		template<class Type, class... Args>
		void create(Args&& ... args) requires IsActor<Type>
		{
			auto obj = std::make_shared<Type>(std::forward<Args>(args)...);
			this->regist(obj);
		}

		template<class Type>
		void regist(const std::shared_ptr<Type>& actor) requires IsActor<Type>
		{
			actor->setWorld(this);
			actor->initView();
			m_worldModel.pushActor(actor);
		}
	};

	using WorldFacade = World;
}