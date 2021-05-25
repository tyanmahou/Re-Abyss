#pragma once
#include <memory>
#include <abyss/utils/Singleton.hpp>
namespace abyss::Resource::Preload
{
    struct PreloadInfo;

    class Manager final : protected Singleton<Manager>
    {
        friend class Singleton<Manager>;
    public:
        static PreloadInfo GetInfo(const s3d::String& preloadName);

        static void Release();
    private:
        Manager();
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}