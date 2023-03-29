#include <abyss/scenes/Scene/SaveSelect/Scene.hpp>

#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

#include <abyss/scenes/Sys/System.hpp>
#include <abyss/scenes/Scene/SaveSelect/Booter.hpp>

namespace abyss::Scene::SaveSelect
{
    class Scene::Impl final:
        public Cycle::SaveSelect::IMasterObserver
    {
    public:
        Impl(const InitData& init) :
            m_data(init._s)
        {
        }

        void loading()
        {
            Resource::Assets::Main()->release();

            Resource::Preload::Preloader preloader(U"Scene/SaveSelect");
            preloader.preload();

            this->init();
        }
#if ABYSS_NO_BUILD_RESOURCE
        void reload()
        {
            Resource::Preload::ParamAll().preload(Resource::Assets::Norelease());
            Resource::Assets::Norelease()->release();

            this->loading();
        }
#endif
        void init()
        {
            m_system = Factory::System::SaveSelect(m_data.get())
                .instantiate<Sys2::System>();
            m_system->boot<Booter>(this);
        }
        void update()
        {
            m_system->update();
        }

        void draw() const
        {
            m_system->draw();
        }

        bool onNewGame(s3d::int32 userId) override
        {
            return this->onSceneEnd({
                .userId = userId,
                .isNewGame = true
            });
        }
        bool onLoadGame(s3d::int32 userId) override
        {
            return this->onSceneEnd({
                .userId = userId,
                .isNewGame = false
            });
        }
        bool onBack() override
        {
            return this->onSceneEnd({
                .isBack = true
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
        std::shared_ptr<Data_t> m_data;
    };
    Scene::Scene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        // ローディング
        m_pImpl->loading();

#if ABYSS_NO_BUILD_RESOURCE
        m_reloader
            .setMessage(U"SaveSelect")
            .setCallback([this]() {
            m_pImpl->reload();
        })
            .setSuperCallback([this] {
            m_pImpl->init();
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
