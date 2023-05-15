#pragma once
#include <abyss/commons/Path.hpp>

namespace abyss
{
    class BgmPath
    {
    public:
        inline static s3d::FilePath Title = Path::SoundPath + U"bgm/Title/title.aas";
        inline static s3d::FilePath StageResult = Path::SoundPath + U"bgm/Main/Common/clear.aas";
    };
}
