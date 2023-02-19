#pragma once
#include <abyss/commons/Msg/Label.hpp>
#include <abyss/commons/Msg/Language.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss::Msg
{
    class Manager final : protected DynamicSingleton<Manager>
    {
        friend class DynamicSingleton<Manager>;
    public:
        static void Load(const Language& lang = Language::Ja());

        static const s3d::String& Get(const Label& label);
    private:
        Manager();
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };

    const s3d::String& Text(const Label& label);
    const s3d::String& Text(const s3d::String& category, const s3d::String& key);
}
