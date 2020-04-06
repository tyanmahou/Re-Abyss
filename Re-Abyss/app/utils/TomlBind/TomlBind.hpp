#pragma once
#include <Siv3D/TOMLReader.hpp>

namespace abyss
{
    template<class Type>
    struct TomlBind
    {
        Type operator()(const s3d::TOMLValue& toml);
    };
}

/*

 example:

 namespace abyss
 {
     template<>
     struct TomlBind<Hoge>
     {
         Hoge operator()(const s3d::TOMLValue& toml){
             // something
             return hoge;
         }
     }
 }

*/