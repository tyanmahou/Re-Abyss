#pragma once
#include <Siv3D/JSONReader.hpp>
#include <Siv3D/Array.hpp>
#include <abyss/utils/Singleton.hpp>

namespace abyss::Resource::Preload
{
    class Manager final : protected Singleton<Manager>
    {
        friend class Singleton<Manager>;
    private:
        Manager();
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}