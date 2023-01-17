#pragma once
#include <abyss/utils/TOML/TOMLBindDef.hpp>

namespace abyss
{
    class TOMLUtil
    {
    public:
        template<class Type>
        static Type FromTOML(const s3d::TOMLValue& toml)
        {
            return TOMLBinding<Type>(toml);
        }
    };
}
