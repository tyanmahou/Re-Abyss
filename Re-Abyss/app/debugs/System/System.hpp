#pragma once
#if ABYSS_DEBUG
#include <memory>
#include <functional>
#include <abyss/debugs/System/SystemContext.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss::Debug
{
    class Menu;
    class LogViewer;
    class WatchViewer;

	/// <summary>
	/// デバッグシステム
	/// </summary>
	class System : private DynamicSingleton<System>
	{
        friend class DynamicSingleton<System>;
    public:
		static bool Apply(std::function<bool()> callback);

        static const SystemContext& Context();
        static void SetContext(const SystemContext& context);
    private:
        System();
        ~System();
    private:
        friend class MenuUtil;
        static Menu& GetMenu();

        friend class Log;
        static LogViewer& GetLogViewer();

        friend class Watcher;
        static WatchViewer& GetWatchViewer();
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}
#endif
