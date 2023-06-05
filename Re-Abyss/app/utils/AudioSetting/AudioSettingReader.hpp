#pragma once
#include <Siv3D/Audio.hpp>
#include <abyss/utils/AudioSetting/AudioSetting.hpp>

namespace abyss
{
    class AudioSettingReader
    {
    public:
        AudioSetting load(const s3d::TOMLValue& toml) const;

        AudioSetting load(const s3d::FilePath& basePath, const s3d::TOMLValue& toml) const;

        AudioSetting load(const s3d::FilePath& path) const;
    };
}
