#pragma once
#include <memory>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss::Resource::Preload
{
    struct PreloadInfo;

    class Manager final : protected DynamicSingleton<Manager>
    {
        friend class DynamicSingleton<Manager>;
    public:
        static PreloadInfo GetInfo(const s3d::String& preloadName);
    private:
        Manager();
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}