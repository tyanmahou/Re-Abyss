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
        {
            // ローディング
            m_data->loader.startAsync(std::bind(&Impl::loading, this));
        }
        void loading()
        {
            // マイグレーション適用
            Resource::UserData::Migration::Update();

            // フォントロード
            Resource::FontRegister::Load();

            auto* assets = Resource::Assets::Norelease();
            // 最初にParam全部ロード
            {
                auto param = Resource::Preload::ParamAll();
                param.preload(assets);
            }
            // Meesage
            {
                auto message = Resource::Preload::Message();
                message.preload(assets);
            }
            // 一度キャッシュ削除
            assets->release();

            // Norelease
            {
                Resource::Preload::Preloader norelease(U"Norelease");
                norelease.preload(assets);
            }
        }
    };
    Scene::Scene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
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
