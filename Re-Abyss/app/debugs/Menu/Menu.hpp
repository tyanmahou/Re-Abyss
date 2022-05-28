#pragma once

#if ABYSS_DEBUG
#include <memory>
#include <any>
#include <Siv3D/String.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>
#include <abyss/debugs/Menu/DebugFlag.hpp>

namespace abyss::Debug
{
    class Menu : protected DynamicSingleton<Menu>
    {
        friend class DynamicSingleton<Menu>;
    public:
        static void Update();

        static bool IsDebug(const s3d::String& label);
        static size_t DebugSelect(const s3d::String& label);

        static void Bind(const s3d::String& key, const std::any& object);
        static const std::any& GetBindObject(const s3d::String& key);
        template<class Type>
        static Type GetBind(const s3d::String& key)
        {
            return std::any_cast<Type>(GetBindObject(key));
        }
        static bool IsRequestedClose();
        static void RequestClose();
        static void ResetRequestClose();
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;

        Menu();
    };
}

#endif