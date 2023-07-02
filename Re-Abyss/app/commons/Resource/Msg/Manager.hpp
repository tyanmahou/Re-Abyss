#pragma once
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Resource/Msg/Label.hpp>
#include <abyss/commons/Resource/Msg/Language.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss::Resource::Msg
{
    class Manager final : protected DynamicSingleton<Manager>
    {
        friend class DynamicSingleton<Manager>;
    public:
        static void Load(const Language& lang = Language::Ja(), Assets* pAssets = Assets::Temporray());

        static const s3d::String& Get(const Label& label);
    private:
        Manager();
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}
