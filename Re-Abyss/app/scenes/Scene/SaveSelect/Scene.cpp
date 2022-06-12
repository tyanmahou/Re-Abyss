#include <abyss/scenes/Scene/SaveSelect/Scene.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

#include <abyss/scenes/System/System.hpp>
#include <abyss/scenes/Scene/SaveSelect/Booter.hpp>

namespace abyss::Scene::SaveSelect
{
    class Scene::Impl final:
        public Cycle::SaveSelect::IMasterObserver
    {
        using System = Sys::System<Sys::Config::SaveSelect()>;
        std::unique_ptr<System> m_system;

        std::function<void()> m_onLoadGameFunc;
        std::function<void()> m_onNewGameFunc;
        std::function<void()> m_onBackFunc;

    public:
        Impl([[maybe_unused]] const InitData& init)
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
            Resource::Assets::Norelease()->release();
            Resource::Assets::Main()->release();
            Resource::Preload::LoadCycleCommon();
            Resource::Preload::LoadSaveSelectToml();
            Resource::Preload::LoadUIToml();

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

        void draw() const
        {
            m_system->draw();
        }

        bool onNewGame() override
        {
            if (m_onNewGameFunc) {
                m_onNewGameFunc();
                return true;
            }
            return false;
        }
        bool onLoadGame() override
        {
            if (m_onLoadGameFunc) {
                m_onLoadGameFunc();
                return true;
            }
            return false;
        }
        bool onBack() override
        {
            if (m_onBackFunc) {
                m_onBackFunc();
                return true;
            }
            return false;
        }
        void bindLoadGameFunc(const std::function<void()>& callback)
        {
            m_onLoadGameFunc = callback;
        }
        void bindNewGameFunc(const std::function<void()>& callback)
        {
            m_onNewGameFunc = callback;
        }
        void bindBackFunc(const std::function<void()>& callback)
        {
            m_onBackFunc = callback;
        }
    };
    Scene::Scene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        m_pImpl->bindLoadGameFunc([this] {
            this->changeScene(SceneKind::Stage);
        });
        m_pImpl->bindNewGameFunc([this] {
            this->changeScene(SceneKind::Stage);
        });
        m_pImpl->bindBackFunc([this] {
            this->changeScene(SceneKind::Title);
        });

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
