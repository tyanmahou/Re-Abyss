#include "SaveSelectScene.hpp"
#include <abyss/commons/Resource/Preload/ParamPreloader.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

#include <abyss/modules/Cycle/SaveSelect/Main.hpp>
#include <Siv3D.hpp>
namespace abyss
{
    class SaveSelectScene::Impl : public Cycle::SaveSelect::IMainObserver
    {
        std::function<void()> m_onLoadGameFunc;
        std::function<void()> m_onNewGameFunc;
        std::function<void()> m_onBackFunc;

        std::unique_ptr<Cycle::SaveSelect::Main> m_main;

    public:
        Impl([[maybe_unused]] const InitData& init)
        {
            this->init();
        }

        void reload()
        {
            Resource::Assets::Main()->release();
            this->init();
        }
        void init()
        {
            Resource::Prelaod::LoadSaveSelectToml(*Resource::Assets::Main());
            Resource::Prelaod::LoadUIToml(*Resource::Assets::Main());

            m_main = std::make_unique<Cycle::SaveSelect::Main>(this);
        }
        void update()
        {
            m_main->update();
        }

        void draw() const
        {
            m_main->draw();
        }

        void finally()
        {
            m_main->finally();
        }

        void onNewGame()
        {
            if (m_onNewGameFunc) {
                m_onNewGameFunc();
            }
        }
        void onLoadGame()
        {
            if (m_onLoadGameFunc) {
                m_onLoadGameFunc();
            }
        }
        void onBack()
        {
            if (m_onBackFunc) {
                m_onBackFunc();
            }
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

    void SaveSelectScene::onSceneUpdate()
    {
        m_pImpl->update();
    }

    void SaveSelectScene::onSceneDraw() const
    {
        m_pImpl->draw();
    }
    void SaveSelectScene::finally()
    {
        m_pImpl->finally();
    }
}
