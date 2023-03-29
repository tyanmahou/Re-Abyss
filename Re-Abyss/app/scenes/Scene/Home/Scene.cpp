#include <abyss/scenes/Scene/Home/Scene.hpp>
#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/scenes/Sys/System.hpp>
#include <abyss/scenes/Scene/Home/Booter.hpp>

#include <Siv3D.hpp>

namespace abyss::Scene::Home
{
    class Scene::Impl final :
        public Cycle::Home::IMasterObserver
    {
    public:
        Impl(const InitData& init) :
            m_data(init._s)
        {}

        void loading()
        {
            Resource::Assets::Main()->release();
            Resource::Preload::Preloader preloader(U"Scene/Home");
            preloader.preload();

            this->init();
        }
#if ABYSS_NO_BUILD_RESOURCE
        void reload()
        {
            Resource::Preload::ParamAll().preload(Resource::Assets::Norelease());
            Resource::Assets::Norelease()->release();
            Resource::Assets::Main()->release();

            this->init();
        }
#endif
        void init()
        {
            m_system = Factory::System::Home(m_data.get())
                .instantiate<Sys2::System>();
            m_system->boot<Booter>(this);
        }

        void update()
        {
            m_system->update();
        }
        void draw()
        {
            m_system->draw();
        }
    public:
        bool onStageStart(const s3d::String& mapPath) override
        {
            return onSceneEnd({
                .mapPath = mapPath
            });
        }
        bool onBack()
        {
            return onSceneEnd({
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
            .setMessage(U"Home")
            .setCallback([this]() {
            this->m_pImpl->reload();
        }).setSuperCallback([this] {
            this->m_pImpl->reload();
        });
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
