#pragma once
#include <Siv3D/Audio.hpp>
#include <Siv3D/String.hpp>

namespace abyss
{
    class AudioSetting
    {
    public:

        s3d::Audio load(const s3d::FilePath& path) const;
    };
}