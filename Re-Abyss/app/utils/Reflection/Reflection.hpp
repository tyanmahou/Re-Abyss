#pragma once
#define MKANTA_CHARTYPE char32_t
#include <mkanta.hpp>
#include <Siv3D/String.hpp>
namespace abyss
{
    template<class Type = mkanta::gobal_scope>
    struct Reflect
    {
        template<class PointerType>
        static mkanta::detail::regist_type_t<PointerType> find(const s3d::String& name)
        {
            return mkanta::reflect<Type>::template find<PointerType>(name.c_str());
        }
    };
}