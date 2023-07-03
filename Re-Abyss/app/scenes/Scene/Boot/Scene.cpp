#include <abyss/scenes/Scene/Boot/Scene.hpp>
#include <abyss/scenes/Scene/Boot/Initializer.hpp>

#include <abyss/commons/Resource/UserData/Migration/Migration.hpp>
#include <abyss/commons/Resource/Font/FontRegister.hpp>
#include <abyss/commons/Resource/Preload/Presets.hpp>
#include <abyss/commons/Factory/Scene/Injector.hpp>

namespace abyss::Scene::Boot
{
    using namespace abyss::Resource;

    class Scene::Impl
    {
    public:
        Impl(const InitData& init)
        {
            // Boot時のローディングで即必要なものはココで初期化する
            {
                // フォントロード
                FontRegister::Load();

                // 初期で必要なものロード
                Preload::Presets::Startup().preload(Assets::NoRelease());
            }
            m_data = init._s;

            // ローディング
            m_data->loader.startAsync(std::bind(&Impl::loading, this));
        }
        void loading()
        {
            // マイグレーション適用
            UserData::Migration::Update();

            Initializer::LoadAsset();

            // ロードが必要なシーンデータ初期化もここで行う
            {
                auto injector = Factory::Scene::SequenceData::Injector();
                m_data->dataStore = injector.resolve<User::DataStore>();
                m_data->sound = injector.resolve<Sound::SceneSound>();
            }
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
