#pragma once
#include <memory>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss::Resource::UserData
{
    class Storage final : protected DynamicSingleton<Storage>
    {
        friend class DynamicSingleton<Storage>;
    public:
        class Impl;

        template<class T>
        static std::shared_ptr<T> Get()
        {
            return Instance()->getService<T>();
        }
    private:
        std::shared_ptr<Impl> m_pImpl;
        Storage();

        template<class T>
        std::shared_ptr<T> getService() const;
    };
}