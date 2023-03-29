#include <abyss/scenes/Scene/Stage/Scene.hpp>

#include <abyss/components/Cycle/Main/Master.hpp>

#include <abyss/modules/Temporary/TemporaryData.hpp>
#include <abyss/modules/Stage/StageData.hpp>
#include <abyss/modules/Adv/Project/Project.hpp>
#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/commons/Factory/Stage/Injector.hpp>
#include <abyss/commons/Factory/Adv/Injector.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>

#include <abyss/scenes/Sys/System.hpp>
#include <abyss/scenes/Scene/Stage/Booter.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
#include <abyss/debugs/Debug.hpp>

namespace abyss::Scene::Stage
{
    class Scene::Impl :
        public Cycle::Main::IMasterObserver
    {
    public:
        Impl(const Scene::InitData& init) :
            m_tempData(std::make_shared<TemporaryData>()),
            m_data(init._s)
        {
            if (std::holds_alternative<Context>(m_data->context)) {
                m_context = std::get<Stage::Context>(m_data->context);
            } else {
                m_context.stage = StageDef::Stage0();
            }
        }
        Coro::Generator<double> preloadAsset()
        {
            Resource::Assets::Main()->release();
            Resource::Preload::Preloader loader(m_context.stage.preloadPath());
            for (auto&& p : loader.preloadProgress()) {
                co_yield p;
            }
        }
        Coro::Generator<double> loading()
        {
            co_yield 0.0;
            for (auto&& p : preloadAsset()) {
                co_yield p;
            }
            this->init();
            co_yield 1.0;
        }
#if ABYSS_NO_BUILD_RESOURCE
        void resourceReload()
        {
            Resource::Preload::ParamAll().preload(Resource::Assets::Norelease());
            Resource::Assets::Norelease()->release();
            Resource::Assets::Main()->release();
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
            Actor::Player::PlayerDesc desc{};
            if (isLockPlayer && m_system) {
                desc = m_system
                    ->mod<Actor::Player::PlayerManager>()
                    ->getDescAsDirect();
            }
            m_system = Factory::System::Stage(m_data.get())
                .instantiate<Sys2::System>();
            auto injector = Factory::Stage::Injector(m_context.stage.mapPath());
            m_stageData = injector.instantiate<StageData>();
            m_stageData->setMapName(m_context.stage.mapName());

            if (!m_advProject) {
                m_advProject = Factory::Adv::Injector().instantiate<Adv::Project>();
            }
            BooterNormal booter(this);
            booter.setPlayerDesc(desc)
                .setStageData(m_stageData)
                .setTempData(m_tempData)
                .setAdvProject(m_advProject)
                ;
            m_system->boot(booter);
        }

        void update()
        {
            m_system->update();
            if (m_systemNext) {
                m_system = std::move(m_systemNext);
                m_systemNext = nullptr;
            }
#if ABYSS_DEBUG
            if ((KeyControl + KeyO).down()) {
                Debug::DebugUtil::FileEdit(m_context.stage.mapPath());
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
            m_systemNext = Factory::System::Stage(m_data.get())
                .instantiate<Sys2::System>();

            BooterRestart booter(this);
            booter.setStageData(m_stageData)
                .setTempData(m_tempData)
                .setAdvProject(m_advProject)
                ;
            m_systemNext->boot(booter);
            return true;
        }
        Coro::Generator<double> loadingOnMove(const s3d::String& link, s3d::int32 startId)
        {
            // マップ更新
            m_context.stage = m_context.stage.link(link);

            for (auto&& p : preloadAsset()) {
                co_yield p;
            }
            Actor::Player::PlayerDesc desc = m_system
                ->mod<Actor::Player::PlayerManager>()
                ->getDesc();
            desc.startId = startId;

            m_system = Factory::System::Stage(m_data.get())
                .instantiate<Sys2::System>();
            auto injector = Factory::Stage::Injector(m_context.stage.mapPath());
            m_stageData = injector.instantiate<StageData>();
            m_stageData->setMapName(m_context.stage.mapName());

            BooterNormal booter(this);
            booter.setPlayerDesc(desc)
                .setStageData(m_stageData)
                .setTempData(m_tempData)
                .setAdvProject(m_advProject)
                ;

            m_system->boot(booter);
            co_yield{};
        }
        bool onMoveStage(const s3d::String& link, s3d::int32 startId) override
        {
            m_data->loader.startAsync(loadingOnMove(link, startId));
            return true;
        }
        bool onEscape() override
        {
            return onSceneEnd({
                .isClear = false
            });
        }
        bool onClear() override
        {
            m_tempData->clearFlag(abyss::TempLevel::Exit);
            // BGMの引継ぎ
            m_data->share.bgmBridge
                .set(m_system->mod<Sound>()->getBgm());

            return onSceneEnd({
                .isClear = true
            });
        }

        bool onSceneEnd(const SceneResult& result)
        {
            m_data->isRequestedSceneEnd = true;
            m_data->result = result;
            return true;
        }
    private:
        std::shared_ptr<Sys2::System> m_system;
        std::shared_ptr<Sys2::System> m_systemNext;
        std::shared_ptr<StageData> m_stageData;
        std::shared_ptr<TemporaryData> m_tempData;
        std::shared_ptr<Adv::Project> m_advProject;

        Context m_context;
        std::shared_ptr<Data_t> m_data;
    };

    Scene::Scene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        getData().loader.startAsync(m_pImpl->loading());

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
    Scene::~Scene()
    {}
    void Scene::onSceneUpdate()
    {
        m_pImpl->update();
    }
    void Scene::onSceneDraw() const
    {
        m_pImpl->draw();
    }
}
