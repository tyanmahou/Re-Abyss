#include <abyss/scenes/SaveSelect/SaveSelectScene.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

#include <abyss/system/System.hpp>
#include <abyss/system/SaveSelect/Booter.hpp>

namespace abyss
{
    class SaveSelectScene::Impl final:
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
            auto booter = std::make_unique<Sys::SaveSelect::Booter>(this);
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
    SaveSelectScene::SaveSelectScene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        m_pImpl->bindLoadGameFunc([this] {
            this->changeScene(SceneName::Main);
        });
        m_pImpl->bindNewGameFunc([this] {
            this->changeScene(SceneName::Main);
        });
        m_pImpl->bindBackFunc([this] {
            this->changeScene(SceneName::Title);
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
    SaveSelectScene::~SaveSelectScene()
    {}
    void SaveSelectScene::onSceneUpdate()
    {
        m_pImpl->update();
    }

    void SaveSelectScene::onSceneDraw() const
    {
        m_pImpl->draw();
    }
}
