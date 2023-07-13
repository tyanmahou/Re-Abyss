#pragma once

namespace abyss
{
    class IApplication;

    class AppRunner
    {
    public:
        bool run(IApplication* pApp) const;
    };
}
