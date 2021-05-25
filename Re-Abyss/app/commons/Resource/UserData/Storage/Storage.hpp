#pragma once
#include <memory>
#include <abyss/utils/Singleton.hpp>

namespace abyss::Resource::UserData
{
    class Storage final : protected Singleton<Storage>
    {
        friend class Singleton<Storage>;
    public:
        class Impl;

        template<class T>
        static std::shared_ptr<T> Get()
        {
            return Instance()->getService<T>();
        }

        static void Release();
    private:
        std::shared_ptr<Impl> m_pImpl;
        Storage();

        template<class T>
        std::shared_ptr<T> getService() const;
    };
}