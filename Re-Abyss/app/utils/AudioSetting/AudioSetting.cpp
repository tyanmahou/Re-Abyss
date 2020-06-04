#include "AudioSetting.hpp"
#include <Siv3D.hpp>
#include <abyss/utils/FileUtil/FileUtil.hpp>
namespace abyss
{
    s3d::Audio abyss::AudioSetting::load(const s3d::FilePath& path) const
    {
        s3d::Audio ret;

        TOMLReader toml(path);
        if (!toml) {
            return ret;
        }
        if (auto audioPath = toml[U"Audio.path"].getOpt<String>()) {
            ret = Audio(FileUtil::ParentPath(path) + *audioPath);
        }
        if (auto loop = toml[U"Audio.loop"].getOpt<bool>()) {
            ret.setLoop(*loop);
        }else if (auto loop = toml[U"Audio.loop"].getOpt<Vec2>()) {
            ret.setLoop(Duration(loop->x), Duration(loop->y));
        }
        return ret;
    }
}
