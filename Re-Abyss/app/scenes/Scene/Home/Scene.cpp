#include <abyss/scenes/Scene/Home/Scene.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/scenes/System/System.hpp>
#include <abyss/scenes/Scene/Home/Booter.hpp>

#include <Siv3D.hpp>

namespace abyss::Scene::Home
{
    class Scene::Impl :
        public Cycle::Home::IMasterObserver
    {
        using System = Sys::System<Sys::Config::Home()>;
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
            Resource::Assets::Norelease()->release();
            Resource::Assets::Main()->release();

            this->init();
        }
#endif
        void init()
        {
            m_system = std::make_unique<System>();
            auto booter = std::make_unique<Booter>(this);
            m_system->boot(booter.get());
        }

        void update()
        {
            m_system->update();
        }
        void draw()
        {
            m_system->draw();
        }
    private:
        std::unique_ptr<System> m_system;
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
