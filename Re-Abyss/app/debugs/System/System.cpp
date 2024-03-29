﻿#include <abyss/debugs/System/System.hpp>
#if ABYSS_DEBUG
#include <abyss/commons/Constants.hpp>
#include <abyss/utils/FPS/FrameRateController.hpp>
#include <abyss/debugs/FPSViewer/FPSViewer.hpp>
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Log/LogViewer.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <abyss/debugs/Pause/Pause.hpp>
#include <abyss/debugs/Watcher/Watcher.hpp>
#include <abyss/debugs/Watcher/WatchViewer.hpp>
#include <Siv3D.hpp>

namespace abyss::Debug
{
	class PauseTrigger : public IPauseEventTrigger
	{
    public:
        PauseTrigger(
            Menu& menu,
            bool& isDrawDebugViewer
        ):
            m_menu(menu),
            m_isDrawDebugViewer(isDrawDebugViewer)
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
            m_isDrawDebugViewer = true;
            m_menu.open();
        }
		void onResume() override
		{
            m_menu.close();
        }
    private:
        Menu& m_menu;
        bool& m_isDrawDebugViewer;
	};
	class System::Impl
	{
	public:
		Impl():
			m_rt(Constants::AppResolution)
		{
			m_pause.setEvent(std::make_unique<PauseTrigger>(m_menu, m_isDrawDebugViewer));
			m_fpsViewer.setPrinter([](s3d::int32 fps){
				Watcher::Print(U"[FPS] {}"_fmt(fps));
			});

            FrameRateController::Setup();
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
            m_log.update();
            m_watcher.update();

			// FPS制御
			m_fpsViewer.update();

			m_pause.update();

            if (KeyF9.down()) {
                m_isDrawDebugViewer = !m_isDrawDebugViewer;
            }
            if (m_isDrawDebugViewer) {
                if (this->isPause()) {
                    m_menu.update();
                }
            }
		}

		void draw() const
		{
			m_rt.draw();
            if (m_isDrawDebugViewer) {
                m_log.draw();
                m_watcher.draw();
                if (this->isPause()) {
                    m_menu.draw();
                }
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
        LogViewer& log()
        {
            return m_log;
        }
        WatchViewer& watcher()
        {
            return m_watcher;
        }
	private:
        SystemContext m_context;
        Pause m_pause;
        Menu m_menu;
		FPSViewer m_fpsViewer;
		s3d::RenderTexture m_rt;
        LogViewer m_log;
        WatchViewer m_watcher;

        bool m_isDrawDebugViewer = true;
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
    LogViewer& System::GetLogViewer()
    {
        return Instance()->m_pImpl->log();
    }
    WatchViewer& System::GetWatchViewer()
    {
        return Instance()->m_pImpl->watcher();
    }
}
#endif
