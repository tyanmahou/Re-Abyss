#include <abyss/scenes/Scene/Boot/Scene.hpp>

#include <abyss/commons/Resource/UserData/Migration/Migration.hpp>
#include <abyss/commons/Resource/Font/FontRegister.hpp>
#include <abyss/commons/Resource/Msg/Manager.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>
#include <abyss/commons/Factory/Storage/Injector.hpp>
#include <abyss/commons/Factory/Sound/Injector.hpp>

namespace abyss::Scene::Boot
{
    class Scene::Impl
    {
    public:
        Impl(const InitData& init)
        {
            // Boot時のローディングで即必要なものはココで初期化する
            {
                // フォントロード
                Resource::FontRegister::Load();

                // 初期で必要なものロード
                Resource::Preload::ParamStartup().preload();
            }
            m_data = init._s;

            // ローディング
            m_data->loader.startAsync(std::bind(&Impl::loading, this));
        }
        void loading()
        {
            // マイグレーション適用
            Resource::UserData::Migration::Update();

            auto* assets = Resource::Assets::Norelease();
            // 最初にParam全部ロード
            {
                auto param = Resource::Preload::ParamAll();
                param.preload(assets);
            }
            // Meesage
            {
                Resource::Msg::Manager::Load();
            }
            // 一度キャッシュ削除
            assets->release();

            // Norelease
            {
                Resource::Preload::Preloader norelease(U"Norelease");
                norelease.preload(assets);
            }

            // ロードが必要なシーンデータ初期化もここで行う
            m_data->dataStore = Factory::Storage::Injector().instantiate<User::DataStore>();
            m_data->sound = std::make_shared<Sound::SceneSound>(
                Factory::Sound::SoundBank::Injector().resolve<Sound::ISoundBank>()
            );
        }
    private:
        std::shared_ptr<SequecneData> m_data;
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
