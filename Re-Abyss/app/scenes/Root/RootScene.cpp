#include <abyss/scenes/Root/RootScene.hpp>

#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/commons/Resource/Preload/Message.hpp>

namespace abyss
{
    class RootScene::Impl
    {
        std::shared_ptr<Data_t> m_data;
    public:
        Impl([[maybe_unused]] const InitData& init) :
            m_data(init._s)
        {}
        Coro::Generator<double> loading()
        {
            // 最初にToml全部ロード
            if (auto* assets = Resource::Assets::Norelease()) {
#if ABYSS_DEBUG
                assets->setWarnMode(false);
#endif
                Resource::Preload::LoadTomlAll(assets);
                Resource::Preload::LoadMessage(U"ja", assets);
                assets->release();
#if ABYSS_DEBUG
                assets->setWarnMode(true);
#endif
            }

            {
                Resource::Preload::Preloader norelease(U"Norelease");
                for (auto&& p : norelease.preloadProgress(Resource::Assets::Norelease())) {
                    co_yield p;
                }
            }
        }
    };
    RootScene::RootScene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        // ローディング
        m_loading.start(m_pImpl->loading());
    }
    RootScene::~RootScene()
    {}
    void RootScene::onSceneUpdate()
    {
        this->changeScene(SceneName::Splash, 0);
    }

    void RootScene::onSceneDraw() const
    {
    }
}
