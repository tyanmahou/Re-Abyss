#include <abyss/debugs/System/System.hpp>
#if ABYSS_DEBUG
#include <abyss/commons/Constants.hpp>
#include <abyss/utils/FPS/FrameRateHz.hpp>
#include <abyss/debugs/FPSViewer/FPSViewer.hpp>
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <abyss/debugs/Pause/Pause.hpp>
#include <Siv3D.hpp>
#include <abyss/utils/DebugLog/DebugLog.hpp>

namespace abyss::Debug
{
	class PauseTrigger : public IPauseEventTrigger
	{
    public:
        PauseTrigger(Menu& menu):
            m_menu(menu)
        {}
		bool isPauseTrigger() const override
		{
			return KeyF11.down();
		}
		bool isResumeTrigger() const override
		{
			return isPauseTrigger() || !m_menu.isOpend();
		}

        void onPause() override
        {
            m_menu.open();
        }
		void onResume() override
		{
            m_menu.close();
        }
    private:
        Menu& m_menu;
	};
	class System::Impl
	{
	public:
		Impl():
			m_rt(Constants::AppResolution)
		{
			m_pause.setEvent(std::make_unique<PauseTrigger>(m_menu));
			m_fpsViewer.setPrinter([](s3d::int32 fps){
				Log.Update << fps;
			});
		}
		bool isPause() const
		{
			return m_pause.isPause();
		}
		bool isUpdate1f() const
		{
			return m_pause.isUpdate1f();
		}
		void update()
		{
			// ログ更新
			Debug::LogUpdater::Update();
            m_log.update();

			// FPS制御
			m_fpsViewer.update();
			FrameRateHz::Sleep();

			m_pause.update();

            if (this->isPause()) {
                m_menu.update();
            }
		}

		void draw() const
		{
			m_rt.draw();
            m_log.draw();
			if (this->isPause()) {
                m_menu.draw();
			}
		}

		bool apply(std::function<bool()> callback)
		{
			this->update();

			bool ret = true;
			if (!this->isPause() || this->isUpdate1f()) {
				m_rt.clear(ColorF(0, 1));
				s3d::ScopedRenderTarget2D scoped(m_rt);
				ret = callback();
			}
			this->draw();

			return ret;
		}

        const SystemContext& context()
        {
            return m_context;
        }
        void setContext(const SystemContext& context)
        {
            m_context = context;
        }
        Menu& menu()
        {
            return m_menu;
        }
	private:
        SystemContext m_context;
        Pause m_pause;
        Menu m_menu;
		FPSViewer m_fpsViewer;
		s3d::RenderTexture m_rt;
        DebugLog::DebugLog m_log;
	};
	System::System() :
		m_pImpl(std::make_unique<Impl>())
	{
	}

	System::~System()
	{
	}
	bool System::Apply(std::function<bool()> callback)
	{
		return Instance()->m_pImpl->apply(std::move(callback));
	}
    const SystemContext& System::Context()
    {
        return Instance()->m_pImpl->context();
    }
    void System::SetContext(const SystemContext& context)
    {
        Instance()->m_pImpl->setContext(context);
    }
    Menu& System::GetMenu()
    {
        return Instance()->m_pImpl->menu();
    }
}
#endif
