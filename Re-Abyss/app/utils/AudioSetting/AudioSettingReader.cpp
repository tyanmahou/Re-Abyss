#include "AudioSettingReader.hpp"
#include <Siv3D.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>

namespace abyss
{
    AudioSetting abyss::AudioSettingReader::load(const s3d::FilePath& basePath, const s3d::TOMLValue& toml) const
    {
        AudioSetting ret;
        if (auto audioPath = toml[U"path"].getOpt<String>()) {
            ret.path = FileUtil::ParentPath(basePath) + *audioPath;
        }
        if (auto loop = toml[U"loop"].getOpt<bool>()) {
            ret.loop = *loop;
        } else if (auto loopBegin = toml[U"loop"].getOpt<double>()) {
            ret.loop = s3d::Duration(*loopBegin);
        } else if (auto loopBeginEnd = toml[U"loop"].getOpt<Vec2>()) {
            ret.loop = s3d::Vector2D<s3d::Duration>{ loopBeginEnd->x, loopBeginEnd->y };
        } else {
            ret.loop = false;
        }
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
