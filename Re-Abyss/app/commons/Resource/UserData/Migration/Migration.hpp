#pragma once
#include <memory>
#include <abyss/utils/Singleton.hpp>

namespace abyss::Resource::UserData
{
    class Migration final : protected Singleton<Migration>
    {
        friend class Singleton<Migration>;
    public:
        static bool Update();
        static void Release();
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
        Migration();
    };
}