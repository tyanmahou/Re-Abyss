#pragma once
#include <abyss/values/Adv/CharaKind.hpp>
#include <abyss/utils/TOML/TOMLUtil.hpp>

namespace abyss::Adv
{
    struct CharaEntity
    {
        [[TOML_BIND(kind)]]
        CharaKind kind;
        [[TOML_BIND(facePath)]]
        s3d::FilePath facePath;
    };
}
