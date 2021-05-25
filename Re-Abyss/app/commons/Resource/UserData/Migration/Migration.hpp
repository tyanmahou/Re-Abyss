#pragma once
#include <memory>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss::Resource::UserData
{
    class Migration final : protected DynamicSingleton<Migration>
    {
        friend class DynamicSingleton<Migration>;
    public:
        static bool Update();
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
        Migration();
    };
}