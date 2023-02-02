#include <abyss/scenes/Scene/Boot/Scene.hpp>

#include <abyss/commons/Resource/UserData/Migration/Migration.hpp>
#include <abyss/commons/Resource/Font/FontRegister.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/commons/Resource/Preload/Message.hpp>

namespace abyss::Scene::Boot
{
    class Scene::Impl
    {
        std::shared_ptr<Data_t> m_data;
    public:
        Impl([[maybe_unused]] const InitData& init) :
            m_data(init._s)
        {}
        Coro::Generator<double> loading()
        {
            // マイグレーション適用
            Resource::UserData::Migration::Update();

            // フォントロード
            Resource::FontRegister::Load();

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
    Scene::Scene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        // ローディング
        getData().loader.startAsync(m_pImpl->loading());
    }
    Scene::~Scene()
    {}
    void Scene::onSceneUpdate()
    {
        this->requestSceneEnd();
    }

    void Scene::onSceneDraw() const
    {
    }
}
