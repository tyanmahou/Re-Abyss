#include "MainScene.hpp"

#include <abyss/components/Cycle/Main/Master.hpp>

#include <abyss/modules/Temporary/TemporaryData.hpp>
#include <abyss/modules/Stage/StageData.hpp>
#include <abyss/factories/Main/MainInjector.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>

#include <abyss/system/System.hpp>
#include <abyss/system/Main/Booter.hpp>

namespace abyss
{
	class MainScene::Impl :
		public Cycle::Main::IMasterObserver
	{
		using System = Sys::System<Sys::Config::Main()>;

		std::unique_ptr<System> m_system;
		std::shared_ptr<StageData> m_stageData;
		std::shared_ptr<TemporaryData> m_tempData;

		String mapName;

		std::shared_ptr<Data_t> m_data;

	public:
		Impl([[maybe_unused]] const MainScene::InitData& init):
			m_tempData(std::make_shared<TemporaryData>()),
			m_data(init._s)
		{
			mapName = U"stage0";
		}

		Coro::Generator<double> loading()
		{
			co_yield 0.0;
			this->init();
			co_yield 1.0;
		}
#if ABYSS_NO_BUILD_RESOURCE
		void reload()
		{
			Resource::Assets::Main()->release();
			Resource::Preload::LoadActorToml();
			Resource::Preload::LoadUIToml();

			this->init(true);
		}
		void superReload()
		{
			m_tempData->clearFlag(abyss::TempLevel::Exit);
			this->init();
		}
#endif
		void init(bool isLockPlayer = false)
		{
			std::shared_ptr<Actor::ActorObj> player = nullptr;
			if (isLockPlayer && m_system) {
				player = m_system
					->mod<Actor::Player::PlayerManager>()
					->getActor()
					.lock();
			}
			m_system = std::make_unique<System>();
			auto injector = Factory::Main::Injector(mapName);
			m_stageData = injector.resolve<StageData>();

			auto booter = std::make_unique<Sys::Main::Booter>(this);
			booter->setInitPlayer(player)
				.setStageData(m_stageData)
				.setTempData(m_tempData);

			m_system->boot(booter.get());
		}

		void update()
		{
			m_system->update();
		}

		void draw() const
		{
			m_system->draw();

		}

		/// <summary>
		/// リスタート処理
		/// </summary>
		/// <returns></returns>
		bool onRestart() override
		{
			m_system = std::make_unique<System>();

			auto booter = std::make_unique<Sys::Main::Booter>(this);
			booter->setBootKind(Sys::Main::BootKind::Restart)
				.setStageData(m_stageData)
				.setTempData(m_tempData);

			m_system->boot(booter.get());
			return true;
		}
		bool onEscape() override
		{
			return false;
		}
		bool onClear() override
		{
			return false;
		}

	};

	MainScene::MainScene(const InitData& init) :
		ISceneBase(init),
		m_pImpl(std::make_unique<Impl>(init))
	{
		m_loading.start(m_pImpl->loading());

#if ABYSS_NO_BUILD_RESOURCE
		m_reloader
			.setMessage(U"stage0")
			.setCallback([this]() {
			    m_pImpl->reload();
		    })
			.setSuperCallback([this] {
				m_pImpl->superReload();
		    })
			;
#endif
	}

	void MainScene::onSceneUpdate()
	{
		m_pImpl->update();
	}
	void MainScene::onSceneDraw() const
	{
		m_pImpl->draw();
	}
}