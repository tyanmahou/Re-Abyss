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

	class ICollisionModel;
	class IWorldView;

	class World
	{
	private:
		WorldModel m_worldModel;
		std::unique_ptr<ICollisionModel> m_collision;
		WorldView m_worldView;

		std::shared_ptr<PlayerActor> m_pPlayer;
		CameraModel* m_pCamera;
	public:
		World();

		void update();

		void reset();

		void draw()const;

		inline void setPlayer(const std::shared_ptr<PlayerActor>& pPlayer){ m_pPlayer = pPlayer; }
		inline const std::shared_ptr<PlayerActor>& getPlayer()const { return m_pPlayer; }

		inline void setCamera(CameraModel* pCamera){ m_pCamera = pCamera; }
		inline CameraModel* getCamera()const { return m_pCamera; }

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