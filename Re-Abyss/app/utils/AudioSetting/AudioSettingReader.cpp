#include <abyss/utils/AudioSetting/AudioSettingReader.hpp>
#include <Siv3D.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
#include "AudioSettingReader.hpp"

namespace abyss
{
    AudioSetting AudioSettingReader::load(const s3d::TOMLValue& toml) const
    {
        AudioSetting ret;
        if (auto audioPath = toml[U"path"].getOpt<String>()) {
            ret.path = *audioPath;
        }
        if (auto loop = toml[U"loop"].getOpt<bool>()) {
            ret.loop = s3d::Loop{ *loop };
        } else if (auto loopBegin = toml[U"loop"].getOpt<double>()) {
            ret.loop = s3d::Duration(*loopBegin);
        } else if (auto loopBeginEnd = toml[U"loop"].getOpt<Vec2>()) {
            ret.loop = s3d::Vector2D<s3d::Duration>{ loopBeginEnd->x, loopBeginEnd->y };
        } else {
            ret.loop = s3d::Loop::No;
        }
        if (auto samplingRate = toml[U"samplingRate"].getOpt<s3d::uint64>()) {
            ret.samplingRate = *samplingRate;
        } else {
            ret.samplingRate = 44100;
        }
        if (auto streaming = toml[U"streaming"].getOpt<bool>()) {
            ret.streaming = *streaming;
        } else {
            ret.streaming = false;
        }
        return ret;
    }
    AudioSetting abyss::AudioSettingReader::load(const s3d::FilePath& basePath, const s3d::TOMLValue& toml) const
    {
        AudioSetting ret = this->load(toml);
        ret.path = FileUtil::ParentPath(basePath) + ret.path;
        return ret;
    }

    AudioSetting abyss::AudioSettingReader::load(const s3d::FilePath& path) const
    {
        TOMLReader toml(path);
        if (!toml) {
            return AudioSetting();
        }
        return this->load(path, toml[U"Audio"]);
    }

}
