#pragma once
#include <abyss/commons/Path.hpp>

namespace abyss
{
    class BgmPath
    {
    public:
        inline static s3d::FilePath Title = Path::BgmPath + U"Title/title.aas";
        inline static s3d::FilePath StageResult = Path::BgmPath + U"Main/Common/clear.aas";
    };
}
