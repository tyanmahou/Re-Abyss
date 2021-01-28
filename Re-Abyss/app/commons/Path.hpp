#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Path
{
    inline s3d::FilePath Root = U"";
    inline s3d::FilePath ResourcePath = U"resources/";
    inline s3d::FilePath PreloadPath = ResourcePath + U"preloads/";
    inline s3d::FilePath ImagePath = ResourcePath + U"images/";
    inline s3d::FilePath MapPath = ResourcePath + U"maps/";
    inline s3d::FilePath ParamPath = ResourcePath + U"params/";
    inline s3d::FilePath ShaderPath = ResourcePath + U"shaders/";
    inline s3d::FilePath SoundPath = ResourcePath + U"sounds/";

    inline s3d::FilePath UserDataPath = U"userdata/";

    inline s3d::FilePath DebugPath = U"debugs/";
}