#include <abyss/scenes/Scene/StageResult/Scene.hpp>
#include <abyss/scenes/System/System.hpp>
#include <abyss/scenes/Scene/StageResult/Booter.hpp>

#include <abyss/debugs/Debug.hpp>

namespace abyss::Scene::StageResult
{
	class Scene::Impl :
        public Cycle::StageResult::IMasterObserver
	{
        using System = Sys::System<Sys::Config::Stage()>;
	public:
		Impl(const InitData& init):
			m_data(init._s)
		{
            this->init();
        }
    public:
        void update()
        {
            m_system->update();
        }

        void draw() const
        {
            m_system->draw();
#if ABYSS_DEBUG
            // TODO 仮メッセージ
            Debug::Watcher::Print(U"--ステージリザルト--\nZでタイトルに戻る");
#endif
        }
    public:
        bool onNextScene()
        {
            m_data->isRequestedSceneEnd = true;
            return true;
        }
    private:
        void init()
        {
            m_system = std::make_unique<System>();
            auto booter = std::make_unique<Booter>(this);
            m_system->boot(booter.get());
            // BGM引継ぎ
            if (auto bgm = m_data->share.bgmBridge.pop()) {
                m_system->mod<Sound>()->setBgm(*bgm);
            }
        }
	private:
		std::shared_ptr<Data_t> m_data;
        std::unique_ptr<System> m_system;
	};

    Scene::Scene(const InitData& init) :
		ISceneBase(init),
		m_pImpl(std::make_unique<Impl>(init))
	{}

    Scene::~Scene()
	{
	}

	void Scene::onSceneUpdate()
	{
        m_pImpl->update();
	}

	void Scene::onSceneDraw() const
	{
        m_pImpl->draw();
	}
}
