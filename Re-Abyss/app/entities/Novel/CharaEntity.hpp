#pragma once
#include <abyss/types/Novel/CharaKind.hpp>
#include <abyss/types/Novel/Name.hpp>
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