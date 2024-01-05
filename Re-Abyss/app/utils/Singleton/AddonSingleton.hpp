#pragma once
#include <Siv3D/Addon.hpp>
#include <abyss/utils/NameOf/NameOf.hpp>
#include <concepts>

namespace abyss
{
    template<class Type>
    class AddonSingleton
    {
    public:
        static Type* Setup()
        {
            return Instance();
        }
        static Type* Instance()
        {
            static Type* instance = [] {
                std::unique_ptr<Type> unique(new Type);
                Addon::Register(NameOf::nameof<Type>(), std::move(unique));
                return Addon::GetAddon<Type>(NameOf::nameof<Type>());
            }();
            return instance;
        }
    protected:
        AddonSingleton() {}
        virtual ~AddonSingleton() {}
    private:
        AddonSingleton(const AddonSingleton& other) = delete;
        AddonSingleton& operator=(const AddonSingleton& other) = delete;
    };
}
