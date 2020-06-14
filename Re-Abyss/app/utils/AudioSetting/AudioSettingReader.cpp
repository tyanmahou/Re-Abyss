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
        } else if (auto loopVec2 = toml[U"loop"].getOpt<Vec2>()) {
            ret.loop = *loopVec2;
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
