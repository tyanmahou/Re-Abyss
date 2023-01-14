#pragma once
#include <abyss/utils/JSON/JSONBind.hpp>

namespace abyss
{
    class JSONUtil
    {
    public:
        template<class Type>
        static Type FromJSON(const s3d::JSON& json)
        {
            return JSONBind<Type>{}.fromJSON(json);
        }

        template<class Type>
        static s3d::JSON ToJSON(const Type& value)
        {
            return JSONBind<Type>{}.toJSON(value);
        }
    };
}
