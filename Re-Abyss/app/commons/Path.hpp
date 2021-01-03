#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Path
{
    inline static s3d::FilePath Root = U"";
    inline static s3d::FilePath ResourcePath = U"resources/";
    inline static s3d::FilePath ImagePath = ResourcePath + U"images/";
    inline static s3d::FilePath MapPath = ResourcePath + U"maps/";
    inline static s3d::FilePath ParamPath = ResourcePath + U"params/";
    inline static s3d::FilePath ShaderPath = ResourcePath + U"shaders/";
    inline static s3d::FilePath SoundPath = ResourcePath + U"sounds/";

    inline static s3d::FilePath UserDataPath = U"userdata/";

    inline static s3d::FilePath DebugPath = U"debugs/";
}