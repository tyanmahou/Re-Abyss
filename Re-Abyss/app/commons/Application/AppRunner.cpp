#include <abyss/commons/Application/AppRunner.hpp>
#include <abyss/commons/Application/base/IApplication.hpp>

namespace abyss
{
    bool AppRunner::run(IApplication* pApp) const
    {
        pApp->onStartup();
        while (System::Update()) {
            if (!pApp->onUpdate()) {
                break;
            }
        }
        pApp->onShutdown();
        return true;
    }
}
