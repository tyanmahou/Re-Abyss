#include <abyss/scenes/Scene/StageResult/Scene.hpp>
#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>

#include <abyss/scenes/Sys/System.hpp>
#include <abyss/scenes/Scene/StageResult/Booter.hpp>

#include <abyss/debugs/Debug.hpp>

namespace abyss::Scene::StageResult
{
	class Scene::Impl :
        public Cycle::StageResult::IMasterObserver
	{
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
            m_system = Factory::System::StageResult(m_data.get())
                .instantiate<Sys::System>();
            m_system->boot<Booter>(this);
            // BGM引継ぎ
            if (auto bgm = m_data->share.bgmBridge.pop()) {
                m_system->mod<Sound>()->setBgm(*bgm);
            }
        }
	private:
		std::shared_ptr<Data_t> m_data;
        std::shared_ptr<Sys::System> m_system;
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
