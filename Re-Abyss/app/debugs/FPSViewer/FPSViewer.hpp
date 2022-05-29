#pragma once
#if ABYSS_DEBUG
#include <functional>
#include <Siv3D/Types.hpp>

namespace abyss::Debug
{
	class FPSViewer
	{
	public:
		void update();

		void setPrinter(std::function<void(s3d::int32)> printer)
		{
			m_printer = printer;
		}
	private:
		bool m_showFps = false;
		std::function<void(s3d::int32)> m_printer;
	};
}
#endif