#pragma once
#include <memory>
#include <unordered_map>
#include <Siv3D/String.hpp>

namespace abyss
{
    namespace detail
    {
        struct ReflectionDummy{};
    }
    template<class Type>
    struct Reflection
    {
        Reflection(const s3d::String& funcName, Type func)
        {
            if (!funcs) {
                funcs = std::make_unique<std::unordered_map<s3d::String, Type>>();
            }
            (*funcs)[funcName] = func;
        }

        static Type Find(const s3d::String& funcName)
        {
            if (!funcs) {
                return nullptr;
            }
            return (*funcs)[funcName];
        }
    private:
        constinit inline static std::unique_ptr<std::unordered_map<s3d::String, Type>> funcs = nullptr;
    };
}

#define REFLECTION(funcName)\
]]inline static abyss::detail::ReflectionDummy _reflect_##funcName##Impl()\
{\
    static const ::abyss::Reflection regist{ U#funcName, &funcName };\
    return {};\
}\
inline static const auto _reflect_##funcName = _reflect_##funcName##Impl();[[
