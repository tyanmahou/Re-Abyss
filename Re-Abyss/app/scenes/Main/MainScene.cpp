#include "MainScene.hpp"

#include <abyss/modules/Master/Master.hpp>

#include <abyss/modules/System/System.hpp>
#include <abyss/modules/Save/SaveData.hpp>
#include <abyss/modules/Stage/StageData.hpp>
#include <abyss/factories/Main/MainInjector.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Resource/Preload/ParamPreloader.hpp>

namespace
{
	using namespace abyss;
	void PreloadResourece(const Resource::Assets& resource)
	{
		Resource::Prelaod::LoadActorToml(resource);
		Resource::Prelaod::LoadUIToml(resource);
	}
}
namespace abyss
{
	class MainScene::Impl :
		public IMasterObserver
	{
		std::unique_ptr<System> m_system;
		std::shared_ptr<StageData> m_stageData;
		std::shared_ptr<SaveData> m_saveData;

		String mapName;

		std::shared_ptr<Data_t> m_data;

	public:
		Impl([[maybe_unused]] const MainScene::InitData& init):
			m_saveData(std::make_shared<SaveData>()),
			m_data(init._s)
		{
			mapName = U"stage0";

			this->init();
		}

		void reload()
		{
			Resource::Assets::Main()->release();
			this->init(true);
		}
		void init(bool isLockPlayer = false)
		{
			std::shared_ptr<Actor::IActor> player = nullptr;
			if (isLockPlayer) {
				player = m_system->lockPlayer();
			}
			m_system = std::make_unique<System>(this);
			auto injector = Factory::Main::Injector(mapName);
			m_stageData = injector.resolve<StageData>();
			m_system->loadStage(m_stageData);
			m_system->loadSaveData(m_saveData);
			::PreloadResourece(*Resource::Assets::Main());
			if (player) {
				m_system->init(player);
			} else {
				m_system->init();
			}
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
			m_system = std::make_unique<System>(this);
			m_system->loadStage(m_stageData);
			m_system->loadSaveData(m_saveData);

			m_system->restart();
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
#if ABYSS_DEBUG
		m_reloader
			.setMessage(U"stage0")
			.setCallback([this]() {
			    m_pImpl->reload();
		    })
			.setSuperCallback([this] {
			    m_pImpl->init();
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