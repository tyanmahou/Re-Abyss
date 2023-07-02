#include <abyss/commons/Resource/Preload/Presets.hpp>
#include <abyss/commons/Resource/Preload/Param.hpp>

namespace abyss::Resource::Preload
{
    Preloader Presets::Startup()
    {
        auto preload = ParamStartup();
        preload.append(U"Startup");
        return preload;
    }
}
