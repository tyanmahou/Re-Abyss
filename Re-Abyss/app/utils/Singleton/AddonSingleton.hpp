#pragma once
#include <Siv3D/Addon.hpp>
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
                Addon::Register(Type::UniqueName(), std::move(unique));
                return Addon::GetAddon<Type>(Type::UniqueName());
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
