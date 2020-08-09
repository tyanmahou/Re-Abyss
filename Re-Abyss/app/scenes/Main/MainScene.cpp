#include "MainScene.hpp"

#include <abyss/controllers/Master/Master.hpp>

#include <abyss/controllers/System/System.hpp>
#include <abyss/controllers/Save/SaveData.hpp>
#include <abyss/factories/Stage/StageDataFactory.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/commons/Resource/Preload/ParamPreloader.hpp>

#include <abyss/debugs/HotReload/HotReload.hpp>

namespace
{
	using namespace abyss;
	void PreloadResourece(const ResourceManager& resource)
	{
		Resource::Prelaod::LoadToml(resource);
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
		ResourceManager m_resources;

		String mapName;

#if ABYSS_DEBUG
		Debug::HotReload m_reloader;
#endif
	public:
		Impl([[maybe_unused]] const MainScene::InitData& init):
			m_saveData(std::make_shared<SaveData>())
		{
			mapName = U"stage0";
#if ABYSS_DEBUG
			m_reloader
				.setMessage(mapName)
				.setCallback([this]() {
					this->reload();
				})
				.setSuperCallback([this] {
					this->init();
				})
			;
#endif
			this->init();
		}

		void reload()
		{
			this->m_resources.release();
			{
				// リロード時はリソースを直で
				m_resources.setIsBuilded(false);
				this->init(true);
			}
		}
		void init(bool isLockPlayer = false)
		{
			std::shared_ptr<Player::PlayerActor> player = nullptr;
			if (isLockPlayer) {
				player = m_system->lockPlayer();
			}
			m_system = std::make_unique<System>(this);
			m_stageData = StageDataFactory::CreateFromTmx(mapName);
			m_system->loadStage(m_stageData);
			m_system->loadSaveData(m_saveData);
			::PreloadResourece(m_resources);
			if (player) {
				m_system->init(player);
			} else {
				m_system->init();
			}
		}

		void update()
		{
#if ABYSS_DEBUG
			m_reloader.detection();
#endif
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
	{}

	void MainScene::update()
	{
		m_pImpl->update();
	}
	void MainScene::draw() const
	{
		m_pImpl->draw();
	}
}