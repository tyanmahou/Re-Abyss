#include <abyss/debugs/System/System.hpp>
#if ABYSS_DEBUG
#include <abyss/commons/Constants.hpp>
#include <abyss/utils/FPS/FrameRateHz.hpp>
#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <abyss/debugs/Log/Log.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <abyss/debugs/Profiler/Profiler.hpp>
#include <abyss/debugs/Pause/Pause.hpp>
#include <Siv3D.hpp>

namespace abyss::Debug
{
	class System::Impl
	{
	public:
		Impl():
			m_rt(Constants::AppResolution)
		{
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
			// FPS制御
			FrameRateHz::Sleep();
			// プロファイラ
			Debug::Profiler::Print();

			Debug::DebugManager::Update();
			m_pause.update();
		}

		void draw() const
		{
			m_rt.draw();
			if (this->isPause()) {
				Debug::Menu::Update();
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
	private:
		Pause m_pause;
		s3d::RenderTexture m_rt;
	};
	System::System() :
		m_pImpl(std::make_unique<Impl>())
	{
	}

	System::~System()
	{
	}
	bool System::apply(std::function<bool()> callback)
	{
		return m_pImpl->apply(std::move(callback));
	}
}
#endif