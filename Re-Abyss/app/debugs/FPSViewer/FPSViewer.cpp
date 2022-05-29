#include <abyss/debugs/FPSViewer/FPSViewer.hpp>
#if ABYSS_DEBUG

#include <Siv3D.hpp>

namespace abyss::Debug
{
	void FPSViewer::update()
	{
        if (KeyF7.down()) {
            m_showFps ^= true;
        }
        if (m_showFps && m_printer) {
            m_printer(Profiler::FPS());
        }
	}
}
#endif

