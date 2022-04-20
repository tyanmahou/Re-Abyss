#include <abyss/scenes/Main/MainScene.hpp>

#include <abyss/components/Cycle/Main/Master.hpp>

#include <abyss/modules/Temporary/TemporaryData.hpp>
#include <abyss/modules/Stage/StageData.hpp>
#include <abyss/modules/Novel/CharaTable.hpp>
#include <abyss/factories/Main/MainInjector.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>

#include <abyss/system/System.hpp>
#include <abyss/system/Main/Booter.hpp>
#include <abyss/debugs/Util/DebugUtil.hpp>

namespace abyss
{
	class MainScene::Impl :
		public Cycle::Main::IMasterObserver
	{
		using System = Sys::System<Sys::Config::Main()>;

		std::unique_ptr<System> m_system;
		std::shared_ptr<StageData> m_stageData;
		std::shared_ptr<TemporaryData> m_tempData;
		std::shared_ptr<Novel::CharaTable> m_charaTable;

		MainSceneContext m_context;

		std::shared_ptr<Data_t> m_data;

		std::function<void()> m_onClearFunc;
	public:
		Impl([[maybe_unused]] const MainScene::InitData& init):
			m_tempData(std::make_shared<TemporaryData>()),
			m_charaTable(std::make_shared<Novel::CharaTable>()),
			m_data(init._s)
		{
			if (std::holds_alternative<MainSceneContext>(m_data->context)) {
				m_context = std::get<MainSceneContext>(m_data->context);
			} else {
				m_context.mapPath = Path::MapPath + U"Stage0.tmx";
			}
		}

		Coro::Generator<double> loading()
		{
			co_yield 0.0;
			Resource::Assets::Main()->release();
#if ABYSS_DEBUG
			String path;
			if (m_context.mapPath.includes(U"tests/data/maps")) {
				path = U"Map/Test";
			} else {
				auto stageKey = s3d::FileSystem::BaseName(m_context.mapPath);
				path = U"Map/{}"_fmt(stageKey);
			}
			Resource::Preload::Preloader loader(path);
#else
			auto stageKey = s3d::FileSystem::BaseName(m_context.mapPath);
			Resource::Preload::Preloader loader(U"Map/{}"_fmt(stageKey));
#endif
			for (auto&& p : loader.preloadProgress()) {
				co_yield p;
			}
			this->init();
			co_yield 1.0;
		}
#if ABYSS_NO_BUILD_RESOURCE
		void resourceReload()
		{
			Resource::Assets::Norelease()->release();
			Resource::Assets::Main()->release();
			Resource::Preload::LoadActorToml();
			Resource::Preload::LoadUIToml();
		}
		void reload()
		{
			this->resourceReload();
			this->init(true);
		}
		void superReload()
		{
			this->resourceReload();
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
			auto injector = Factory::Main::Injector(m_context.mapPath);
			m_stageData = injector.resolve<StageData>();

			auto booter = std::make_unique<Sys::Main::BooterNormal>(this);
			booter->setInitPlayer(player)
				.setStageData(m_stageData)
				.setTempData(m_tempData)
				.setCharaTable(m_charaTable)
				;

			m_system->boot(booter.get());
		}

		void update()
		{
			m_system->update();
#if ABYSS_DEBUG
			if ((KeyControl + KeyO).down()) {
				Debug::DebugUtil::FileEdit(m_context.mapPath);
			}
#endif
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
			using namespace Sys::Main;
			m_system = std::make_unique<System>();

			auto booter = std::make_unique<Sys::Main::BooterRestart>(this);
			booter->setStageData(m_stageData)
				.setTempData(m_tempData)
				.setCharaTable(m_charaTable)
				;
			m_system->boot(booter.get());
			return true;
		}
		bool onEscape() override
		{
			m_tempData->clearFlag(abyss::TempLevel::Exit);
			return false;
		}
		bool onClear() override
		{
			m_tempData->clearFlag(abyss::TempLevel::Exit);
			// BGMの引継ぎ
			m_data->context = ClearResultSceneContext{
				.bgm = m_system->mod<Sound>()->getBgm()
			};

			if (m_onClearFunc) {
				m_onClearFunc();
			}
			return true;
		}

		void bindOnClear(const std::function<void()>& callback)
		{
			m_onClearFunc = callback;
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
		m_pImpl->bindOnClear([this] {
			// Clear画面に遷移
			this->changeScene(SceneName::ClearResult, 0);
		});

	}
	MainScene::~MainScene()
	{}
	void MainScene::onSceneUpdate()
	{
		m_pImpl->update();
	}
	void MainScene::onSceneDraw() const
	{
		m_pImpl->draw();
	}
}