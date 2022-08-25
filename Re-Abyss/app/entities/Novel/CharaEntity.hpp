#pragma once
#include <abyss/modules/Novel/CharaKind.hpp>
#include <abyss/modules/Novel/Name.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Novel
{
    struct CharaEntity
    {
        CharaKind kind{};
        Name name;
        s3d::FilePath facePath;
    };
}
